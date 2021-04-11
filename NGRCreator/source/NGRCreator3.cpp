#include <iostream>
#include <filesystem>
#include <string>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <vector>
#include <locale>
#include <stdlib.h>
//#include <gtk/gtk.h>
//#include <gtkmm/button.h>
//#include <gtkmm/window.h>
using namespace std;


#include <gtkmm.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/application.h>

#define TYPE_UNK 0
#define TYPE_PAL 1
#define TYPE_SPR 2
#define TYPE_ANI 3
#define TYPE_COL 4


struct NGRHeader
{
	//fileheader
	char 		ident[3] 	= {'N', 'G', 'R' };
	uint16_t	numItems 	= 0;
	uint32_t	offsetTOC	= 0;
}__attribute__((__packed__));

struct NGRDataBlock
{
	int size;
	int type;
	string name;
	string path;
	char* data;
};

struct TOCEntry
{
	uint32_t	offset;
	uint32_t	size;
	uint32_t	type;
	char		name[24];
}__attribute__((__packed__));;


class ModelColumns : public Gtk::TreeModel::ColumnRecord
{
public:
	Gtk::TreeModelColumn<unsigned int>		index;
	Gtk::TreeModelColumn<unsigned int>		type;
	Gtk::TreeModelColumn<Glib::ustring> 	typeAlias;
	Gtk::TreeModelColumn<unsigned int> 		size;
	Gtk::TreeModelColumn<Glib::ustring> 	name;
	Gtk::TreeModelColumn<Glib::ustring> 	filepath;
public:
	ModelColumns()
	{
		add( index );
		add( type );
		add( typeAlias );
		add( size );
		add( name );
		add( filepath );
	}
};


class NGREngine
{
protected:
	NGRHeader				header;
	vector<NGRDataBlock>	data;
	vector<TOCEntry> 		TOC;

	vector<string>			filepaths;


	//UI Stuff
	//Gtk::Application app;

	Gtk::Window mainWindow;
	Gtk::Button exitButton;
	Gtk::Button importFilesButton;
	Gtk::Button openFileButton;
	Gtk::Button saveButton;
	Gtk::Button newFileButton;
	Gtk::Button removeButton;
	Gtk::Button saveHeaderButton;
	Gtk::Box verticalBox;
	Gtk::Box horizontalBox;

	Gtk::ScrolledWindow scrollWindow;

	ModelColumns columns;
	Gtk::TreeView::Column nameColumn;
	Gtk::TreeView treeView;
	Glib::RefPtr<Gtk::TreeSelection> treeSelection;
	Glib::RefPtr<Gtk::ListStore> treeModel;
	Gtk::CellRendererText cellRenderer;
public:
	NGREngine()
	{
		//Buttons
		exitButton.set_label( "exit" );
		exitButton.signal_clicked().connect( sigc::mem_fun( this, &NGREngine::Exit ) );
		
		importFilesButton.set_label( "import Files" );
		importFilesButton.signal_clicked().connect( sigc::mem_fun( this, &NGREngine::ImportFiles ) );

		openFileButton.set_label( "open File" );
		openFileButton.signal_clicked().connect( sigc::mem_fun( this, &NGREngine::OpenFile ) );

		saveButton.set_label( "save" );
		saveButton.signal_clicked().connect( sigc::mem_fun( this, &NGREngine::Save ) );

		newFileButton.set_label( "new" );
		newFileButton.signal_clicked().connect( sigc::mem_fun( this, &NGREngine::NewFile ) );

		removeButton.set_label( "remove selected" );
		removeButton.signal_clicked().connect( sigc::mem_fun( this, &NGREngine::RemoveItems ) );

		saveHeaderButton.set_label( "save C Header" );
		saveHeaderButton.signal_clicked().connect( sigc::mem_fun( this, &NGREngine::SaveHeader ) );

		//verticalBox
		verticalBox.set_orientation( Gtk::ORIENTATION_VERTICAL );
		verticalBox.set_spacing( 10 );
		verticalBox.set_border_width( 10 );
		verticalBox.add( newFileButton );
		verticalBox.add( importFilesButton );
		verticalBox.add( removeButton );
		verticalBox.add( openFileButton );
		verticalBox.add( saveButton );
		verticalBox.add( saveHeaderButton );
		verticalBox.add( exitButton );

		//treeview
		treeModel = Gtk::ListStore::create( columns );
		treeView.set_model( treeModel );
		treeView.set_reorderable();

		treeSelection = treeView.get_selection();
		treeSelection->set_mode( Gtk::SELECTION_MULTIPLE );
		treeSelection->selected_foreach_iter( sigc::mem_fun( this, &NGREngine::SelectedRowCallback ) );

		treeView.append_column( "Index", columns.index );
		treeView.append_column( "Type", columns.type );
		treeView.append_column( "TypeAlias", columns.typeAlias );
		treeView.append_column( "Size", columns.size );
		treeView.append_column( "name", columns.name );
		treeView.append_column( "Filepath", columns.filepath );

		Gtk::CellRendererText* nameRenderer = (Gtk::CellRendererText*)treeView.get_column_cell_renderer( 4 );
		nameRenderer->property_editable() = true;
		nameRenderer->signal_edited().connect( sigc::mem_fun( this, &NGREngine::CellsEdited ) );

		//scrolledWindow
		scrollWindow.add( treeView );

		//horizontalBox
		horizontalBox.set_orientation( Gtk::ORIENTATION_HORIZONTAL );
		horizontalBox.add( verticalBox );
		horizontalBox.pack_start( scrollWindow );

		//mainWindow
		mainWindow.set_title( "NGR Builder" );
		mainWindow.set_default_size( 800, 500 );
		mainWindow.add( horizontalBox );

		mainWindow.show_all_children();
	}
	~NGREngine()
	{
		//
		//
	}
	Gtk::Window* GetWindow()
	{
		//
		return &mainWindow;
	}
	void ImportFile( string filePath )
	{
		FILE* file = fopen( filePath.c_str(), "rb" );
		if( file == NULL )
		{
			cout<<"could not open file "<<filePath<<endl;
			Gtk::MessageDialog error( "Error" );
			error.run();
			exit( EXIT_FAILURE );
		}

		// obtain file size:
		fseek ( file , 0 , SEEK_END);
		int fileSize = ftell ( file );
		rewind ( file );

		NGRDataBlock newFile;
		newFile.size = fileSize;
		newFile.data = (char*)malloc( fileSize );
		newFile.path = filePath;
		int bytesRead = fread( newFile.data, 1, fileSize, file );

		newFile.type = GetTypeFromDataBlock( newFile );

		fclose( file );

		cout<<"read "<<filePath<<": allocated "<<fileSize<<" bytes and read "<<bytesRead<<" bytes"<<endl;

		data.push_back( newFile );
	}
	void ImportAllFiles( vector<string> filePaths )
	{
		for( unsigned int i = 0; i < filePaths.size(); i++ )
		{
			ImportFile( filePaths[i] );
		}
	}
	bool compareBytes( char* a, char* b, unsigned int length )
	{
		for( unsigned int i = 0; i < length; i++ )
		{
			if( a[i] != b[i] )
			{
				return false;
			}
		}
		return true;
	}
	void AddAllDataBlocksToTreeView()
	{
		for( unsigned int i = 0; i < data.size(); i++ )
		{
			Gtk::TreeModel::Row row = *(treeModel->append());
			row[columns.index] = i;
			row[columns.type] = data[i].type;
			
			#pragma GCC diagnostic push
    		#pragma GCC diagnostic ignored "-Wclass-memaccess"
			if( data[i].type == TYPE_SPR )
			{
				row[columns.typeAlias] = "Sprite";
			}
			if( data[i].type == TYPE_UNK )
			{
				row[columns.typeAlias] = "Unknown";
			}
			if( data[i].type == TYPE_COL )
			{
				row[columns.typeAlias] = "Collection";
			}
			if( data[i].type == TYPE_PAL )
			{
				row[columns.typeAlias] = "Palette";
			}
			if( data[i].type == TYPE_ANI )
			{
				row[columns.typeAlias] = "Animation";
			}
			#pragma GCC diagnostic pop
			
			row[columns.size] = data[i].size;
			row[columns.filepath] = data[i].path;
			row[columns.name] = data[i].name;
			
		}
	}
	void ExtractNameFromPathForAllBlocks()
	{
		for( unsigned int i = 0; i < data.size(); i++ )
		{
			//extract name
			unsigned int slashPos = data[i].path.find_last_of("/");
			slashPos++;
			unsigned int dotPos = data[i].path.find_first_of(".");
			//row[columns.name] = data[i].path.substr( slashPos, dotPos - slashPos );
			data[i].name = data[i].path.substr( slashPos, dotPos - slashPos );
		}
	}
	void freeAllDataBlocks()
	{
		for( unsigned int i = 0; i < data.size(); i++ )
		{
			free( data[i].data );
		}
		data.clear();
	}
	void ClearTreeView()
	{
		Gtk::TreeModel::Children children = treeModel->children();
		while( children.begin() != children.end() )
		{
			treeModel->erase(children.begin() );
		}

		/*for(Gtk::TreeModel::Children::iterator iter = children.begin(); iter != children.end(); ++iter)
		{
		  Gtk::TreeModel::Row row = *iter;
		  treeModel->erase( row );
		}*/
		//children.clear();
		//treeModel.children();	
	}
	int GetTypeFromDataBlock( NGRDataBlock dataBlock )
	{
		#pragma GCC diagnostic push
    	#pragma GCC diagnostic ignored "-Wwrite-strings"
		if( compareBytes( dataBlock.data, "PAL", 3 ) )
		{
			return TYPE_PAL;
		}
		else if( compareBytes( dataBlock.data, "SPR", 3 ) )
		{
			return TYPE_SPR;
		}
		else if( compareBytes( dataBlock.data, "ANI", 3 ) )
		{
			return TYPE_ANI;
		}
		else if( compareBytes( dataBlock.data, "COL", 3 ) )
		{
			return TYPE_COL;
		}
		else
		{
			return TYPE_UNK;
		}
		#pragma GCC diagnostic pop
	}
	void RunGui()
	{
		//
		//app.run( mainWindow );
	}
	void Exit()
	{
		//app.quit();
		mainWindow.close();
	}
	void ImportFiles()
	{
		ClearTreeView();
		Gtk::FileChooserDialog dialog("Please select Files", Gtk::FILE_CHOOSER_ACTION_OPEN);
		dialog.set_transient_for( mainWindow );
		dialog.set_select_multiple(true);

		//Add response buttons the the dialog:
		dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
		dialog.add_button("Select", Gtk::RESPONSE_OK);

		int result = dialog.run();

		//Handle the response:
		switch(result)
		{
			case(Gtk::RESPONSE_OK):
			{
				vector<string> files = dialog.get_filenames();
				ImportAllFiles( files );
				break;
			}
			case(Gtk::RESPONSE_CANCEL):
			{
				std::cout << "Cancel clicked." << std::endl;
				break;
			}
			default:
			{
				std::cout << "Unexpected button clicked." << std::endl;
				break;
			}
		}

		ExtractNameFromPathForAllBlocks();
		AddAllDataBlocksToTreeView();
	}
	void OpenFile()
	{
		ClearTreeView();
		Gtk::FileChooserDialog dialog("Please select File", Gtk::FILE_CHOOSER_ACTION_OPEN);
		dialog.set_transient_for( mainWindow );
		dialog.set_select_multiple(false);

		//Add response buttons the the dialog:
		dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
		dialog.add_button("Select", Gtk::RESPONSE_OK);

		int result = dialog.run();

		//Handle the response:
		switch(result)
		{
			case(Gtk::RESPONSE_OK):
			{
				vector<string> files = dialog.get_filenames();
				if( files.size() > 0 )
				{
					ReadNGRFile( files[0] );
				}
				break;
			}
			case(Gtk::RESPONSE_CANCEL):
			{
				std::cout << "Cancel clicked." << std::endl;
				break;
			}
			default:
			{
				std::cout << "Unexpected button clicked." << std::endl;
				break;
			}
		}

		//AddAllDataBlocksToTreeView();
	}
	void ReadNGRFile( string filename )
	{
		cout<<"opening file..."<<endl;

		freeAllDataBlocks();
		ClearTreeView();

		FILE* file = fopen( filename.c_str(), "rb" );

		//goto TOC
		NGRHeader header;
		fread( &header, sizeof(NGRHeader), 1, file );
		fseek( file, header.offsetTOC, SEEK_SET );

		cout<<"Header: offset "<<header.offsetTOC<<" items: "<<header.numItems<<endl;

		//read TOC
		vector<TOCEntry> newEntries;
		for( unsigned int i = 0; i < header.numItems; i++ )
		{
			TOCEntry entry;
			fread( &entry, sizeof(TOCEntry), 1, file );
			newEntries.push_back( entry );
			cout<<"TOCEntry: "<<i<<" offset: "<<entry.offset<<" size: "<<entry.size<<" Name: "<<entry.name<<endl;
		}

		//read all data
		for( unsigned int i = 0; i < newEntries.size(); i++ )
		{
			NGRDataBlock newBlock;
			newBlock.size = newEntries[i].size;
			//newblock.type
			newBlock.path = filename;
			newBlock.name = newEntries[i].name;

			rewind( file );
			fseek( file, newEntries[i].offset, SEEK_SET );
			newBlock.data = (char*)malloc( newEntries[i].size );
			fread( newBlock.data, newEntries[i].size, 1, file );

			newBlock.type = GetTypeFromDataBlock( newBlock );

			data.push_back( newBlock );
		}

		AddAllDataBlocksToTreeView();

		cout<<"done opening file!"<<endl;
		fclose( file );
	}
	void NewFile()
	{
		freeAllDataBlocks();
		ClearTreeView();
	}
	void DeleteEntry()
	{
		Gtk::TreeModel::Children children = treeModel->children();
		//treeModel.get_selection();
	}
	void Save()
	{
		Gtk::FileChooserDialog dialog("Please select File", Gtk::FILE_CHOOSER_ACTION_SAVE);
		dialog.set_transient_for( mainWindow );
		dialog.set_select_multiple(false);

		//Add response buttons the the dialog:
		dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
		dialog.add_button("Select", Gtk::RESPONSE_OK);

		int result = dialog.run();

		//Handle the response:
		switch(result)
		{
			case(Gtk::RESPONSE_OK):
			{
				vector<string> files = dialog.get_filenames();

				if( files.size() > 0 )
				{
					SaveDataToFile( files[0] );
				}
				break;
			}
			case(Gtk::RESPONSE_CANCEL):
			{
				std::cout << "Cancel clicked." << std::endl;
				break;
			}
			default:
			{
				std::cout << "Unexpected button clicked." << std::endl;
				break;
			}
		}
	}
	void SaveHeader()
	{
		Gtk::FileChooserDialog dialog("Please select File", Gtk::FILE_CHOOSER_ACTION_SAVE);
		dialog.set_transient_for( mainWindow );
		dialog.set_select_multiple(false);

		//Add response buttons the the dialog:
		dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
		dialog.add_button("Select", Gtk::RESPONSE_OK);

		int result = dialog.run();

		//Handle the response:
		switch(result)
		{
			case(Gtk::RESPONSE_OK):
			{
				vector<string> files = dialog.get_filenames();

				if( files.size() > 0 )
				{
					SaveHeaderFile( files[0] );
				}
				break;
			}
			case(Gtk::RESPONSE_CANCEL):
			{
				std::cout << "Cancel clicked." << std::endl;
				break;
			}
			default:
			{
				std::cout << "Unexpected button clicked." << std::endl;
				break;
			}
		}
	}
	void SaveDataToFile( string filepath )
	{
		//if( filepath.find_first_of( "." ) == string::npos )
		//{
		//	filepath = filepath + ".ngr";
		//}

		FILE* file = fopen( filepath.c_str(), "wb" );
		
		//write Header
		NGRHeader header;
		header.numItems = data.size();
		fwrite( &header, sizeof(NGRHeader), 1,  file );

		uint32_t dataOffset = ftell( file );
		for( unsigned int i = 0; i < data.size(); i++ )
		{
			TOCEntry entry;
			entry.offset = dataOffset;
			entry.size = data[i].size;
			entry.type = data[i].type;
			strcpy( entry.name, data[i].name.c_str() );
			TOC.push_back( entry );

			fwrite( data[i].data, data[i].size, 1, file );
			dataOffset = ftell( file );
		}

		header.offsetTOC = ftell( file );
		//write TOC
		fwrite( &TOC[0], TOC.size() * sizeof( TOCEntry) , 1,  file );

		//write header again;
		rewind( file );
		fwrite( &header, sizeof(NGRHeader), 1,  file );

		fclose( file );
	}
	void SaveHeaderFile( string filepath )
	{
		FILE* file = fopen( filepath.c_str(), "wb" );
		
		//write Header
		fprintf( file, 	"///////////////////////////////////////////////////////////////\n"
						"//                                                           //\n"
						"//                      NGR - Header                         //\n"
						"//                                                           //\n"
						"///////////////////////////////////////////////////////////////\n\n\n");

		fprintf( file, "//============ defines ===============\n");
		uint32_t dataOffset =sizeof(NGRHeader);
		for( unsigned int i = 0; i < data.size(); i++ )
		{
			fprintf( file, "#define %s %i\n", data[i].name.c_str(), dataOffset );
			dataOffset = dataOffset + data[i].size;
		}
		fprintf( file, "//====================================\n");
		//write Footer
		fprintf( file, "//------------------------- End -------------------------//\n");

		fclose( file );
	}
	void RemoveItems()
	{
		vector<Gtk::TreeModel::Path> selectedItems = treeSelection->get_selected_rows();
		for( unsigned int i = 0; i < selectedItems.size(); i++ )
		{
			Gtk::TreeModel::iterator iter = treeView.get_model()->get_iter( selectedItems[i] );	
			Gtk::TreeModel::Row row = *iter;
			cout<<"trying to delete "<<row[columns.index]<<endl;
			int index = row[columns.index]  - i;
			free(data[index].data);
			data.erase( data.begin() + index );
		}
		ClearTreeView();
		AddAllDataBlocksToTreeView();
	}
	void SelectedRowCallback( const Gtk::TreeModel::iterator& iter )
	{
		Gtk::TreeModel::Row row = *iter;
		cout<<row[columns.index]<<endl;
	}
	void SelectionChanged()
	{
		//
		cout<<"changed";
	}
	void CellsEdited(string path, string newText)
	{
		int editIndex = atoi(path.c_str());
		cout<<editIndex<<", "<<newText<<endl;
		data[editIndex].name = newText;
		ClearTreeView();
		AddAllDataBlocksToTreeView();
	}
};




int main(int argc, char *argv[])
{
	auto app = Gtk::Application::create("org.gtkmm.example");

	NGREngine engine;

	app->run( *engine.GetWindow() );

	return 0;
}