#include <gtkmm.h>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

#define TYPE_UNK 0
#define TYPE_PAL 1
#define TYPE_SPR 2
#define TYPE_ANI 3
#define TYPE_COL 4


struct NGRHeader
{
    //fileheader
    char        ident[3]    = {'N', 'G', 'R' };
    uint16_t    numItems    = 0;
    uint32_t    offsetTOC   = 0;
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
    uint32_t    offset;
    uint32_t    size;
    uint32_t    type;
    char        name[24];
}__attribute__((__packed__));;



class ModelColumns : public Gtk::TreeModel::ColumnRecord
{
public:
    Gtk::TreeModelColumn<unsigned int>      index;
    Gtk::TreeModelColumn<unsigned int>      type;
    Gtk::TreeModelColumn<Glib::ustring>     typeAlias;
    Gtk::TreeModelColumn<unsigned int>      size;
    Gtk::TreeModelColumn<Glib::ustring>     name;
    Gtk::TreeModelColumn<Glib::ustring>     filepath;

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

class NGRCreator : public Gtk::Window
{
protected:
    NGRHeader               header;
    vector<NGRDataBlock>    data;
    vector<TOCEntry>        TOC;

    vector<string>          filepaths;

    //Member widgets:
    Gtk::Button m_button;
    Gtk::Button exitButton;
    Gtk::Button importFilesButton;
    Gtk::Button openFileButton;
    Gtk::Button saveButton;
    Gtk::Button newFileButton;
    Gtk::Button removeButton;
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
            NGRCreator                          ();
            ~NGRCreator                         () override;
    //Signal handlers:
    void    on_button_clicked                   ();
    void    Exit                                ();
    void    ImportFiles                         ();
    void    OnImportFileDialogResponse          ( int response_id, Gtk::FileChooserDialog* dialog );
    void    ClearTreeView                       ();
    void    ImportAllFiles                      ( vector<string> filePaths );
    void    ExtractNameFromPathForAllBlocks     ();
    void    AddAllDataBlocksToTreeView          ();
    void    ImportFile                          ( string filePath );
    int     GetTypeFromDataBlock                ( NGRDataBlock dataBlock );
    bool    CompareBytes                        ( char* a, char* b, unsigned int length );
    void    OpenFile                            ();
    void    OnOpenFileDialogResponse            ( int response_id, Gtk::FileChooserDialog* dialog );
    void    ReadNGRFile                         ( string filename );
    void    FreeAllDataBlocks                   ();
    void    Save                                ();
    void    OnSaveFileDialogResponse            ( int response_id, Gtk::FileChooserDialog* dialog );
    void    SaveDataToFile                      ( string filepath );
    void    NewFile                             ();
    void    freeAllDataBlocks                   ();
    void    RemoveItems                         ();
    void    SelectedRowCallback                 ( const Gtk::TreeModel::iterator& iter );
    void    SelectionChanged                    ();
    void    CellsEdited                         ( string path, string newText );

};

NGRCreator::NGRCreator() : m_button( "Hello World" )   // creates a new button with label "Hello World".
{
    // Sets the margin around the button.
    m_button.set_margin( 10 );

    // When the button receives the "clicked" signal, it will call the
    // on_button_clicked() method defined below.
    m_button.signal_clicked().connect( sigc::mem_fun( *this, &NGRCreator::on_button_clicked ) );

    //Buttons
    exitButton.set_label( "exit" );
    exitButton.signal_clicked().connect( sigc::mem_fun( *this, &NGRCreator::Exit ) );

    importFilesButton.set_label( "import Files" );
    importFilesButton.signal_clicked().connect( sigc::mem_fun( *this, &NGRCreator::ImportFiles ) );

    openFileButton.set_label( "open File" );
    openFileButton.signal_clicked().connect( sigc::mem_fun( *this, &NGRCreator::OpenFile ) );

    saveButton.set_label( "save" );
    saveButton.signal_clicked().connect( sigc::mem_fun( *this, &NGRCreator::Save ) );

    newFileButton.set_label( "new" );
    newFileButton.signal_clicked().connect( sigc::mem_fun( *this, &NGRCreator::NewFile ) );

    removeButton.set_label( "remove selected" );
    removeButton.signal_clicked().connect( sigc::mem_fun( *this, &NGRCreator::RemoveItems ) );



    //verticalBox
    verticalBox.set_orientation( Gtk::Orientation::VERTICAL );
    verticalBox.set_spacing( 10 );
    verticalBox.set_margin( 10 );
    verticalBox.append( newFileButton );
    verticalBox.append( importFilesButton );
    verticalBox.append( removeButton );
    verticalBox.append( openFileButton );
    verticalBox.append( saveButton );
    verticalBox.append( exitButton );

    //treeview
    treeModel = Gtk::ListStore::create( columns );
    treeView.set_model( treeModel );
    treeView.set_reorderable();

    treeSelection = treeView.get_selection();
    treeSelection->set_mode( Gtk::Selection::MULTIPLE );
    treeSelection->selected_foreach_iter( sigc::mem_fun( *this, &NGRCreator::SelectedRowCallback ) );

    treeView.append_column( "Index", columns.index );
    treeView.append_column( "Type", columns.type );
    treeView.append_column( "TypeAlias", columns.typeAlias );
    treeView.append_column( "Size", columns.size );
    treeView.append_column( "name", columns.name );
    treeView.append_column( "Filepath", columns.filepath );

    Gtk::CellRendererText* nameRenderer = (Gtk::CellRendererText*)treeView.get_column_cell_renderer( 4 );
    nameRenderer->property_editable() = true;
    nameRenderer->signal_edited().connect( sigc::mem_fun( *this, &NGRCreator::CellsEdited ) );

    //scrolledWindow
    scrollWindow.set_child( treeView );

    //horizontalBox
    horizontalBox.set_orientation( Gtk::Orientation::HORIZONTAL );
    horizontalBox.append( verticalBox );
    horizontalBox.append( scrollWindow );

    //mainWindow
    set_title( "NGR Builder" );
    set_default_size( 800, 500 );
    set_child( horizontalBox );

    //mainWindow.show_all_children();
}

NGRCreator::~NGRCreator()
{
}

void NGRCreator::on_button_clicked()
{
    cout << "Hello World" << endl;
}

void NGRCreator::Exit()
{
    //quit();
}

void NGRCreator::ImportFiles()
{
    ClearTreeView();
    auto dialog = new Gtk::FileChooserDialog( "Please select Files", Gtk::FileChooser::Action::OPEN );
    dialog->set_transient_for( *this );
    dialog->set_select_multiple( true );

    //Add response buttons the the dialog:
    dialog->add_button( "Cancel", Gtk::ResponseType::CANCEL );
    dialog->add_button( "Select", Gtk::ResponseType::OK );
    dialog->signal_response().connect( sigc::bind( sigc::mem_fun( *this, &NGRCreator::OnImportFileDialogResponse ), dialog ) );
}

void NGRCreator::OnImportFileDialogResponse( int response_id, Gtk::FileChooserDialog* dialog )
{
    //Handle the response:
    switch ( response_id )
    {
        case Gtk::ResponseType::OK:
        {
            std::cout << "Open clicked." << std::endl;

            vector<string> files = dialog->get_files();
            ImportAllFiles( files );
            break;
        }
        case Gtk::ResponseType::CANCEL:
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

    delete dialog;
}

void NGRCreator::ClearTreeView()
{
    Gtk::TreeModel::Children children = treeModel->children();
    while( children.begin() != children.end() )
    {
        treeModel->erase(children.begin() );
    }
}
void NGRCreator::ImportAllFiles( vector<string> filePaths )
{
    for( unsigned int i = 0; i < filePaths.size(); i++ )
    {
        ImportFile( filePaths[i] );
    }
}
void NGRCreator::ExtractNameFromPathForAllBlocks()
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
void NGRCreator::AddAllDataBlocksToTreeView()
{
    for( unsigned int i = 0; i < data.size(); i++ )
    {
        Gtk::TreeModel::Row row = *(treeModel->append());
        row[columns.index] = i;
        row[columns.type] = data[i].type;
        
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
        
        row[columns.size] = data[i].size;
        row[columns.filepath] = data[i].path;
        row[columns.name] = data[i].name;
        
    }
}
void NGRCreator::ImportFile( string filePath )
{
    FILE* file = fopen( filePath.c_str(), "rb" );
    if( file == NULL )
    {
        cout<<"could not open file "<<filePath<<endl;
        Gtk::MessageDialog error( "Error" );
        error.present();
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
int NGRCreator::GetTypeFromDataBlock( NGRDataBlock dataBlock )
{
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wwrite-strings"
    if( CompareBytes( dataBlock.data, "PAL", 3 ) )
    {
        return TYPE_PAL;
    }
    else if( CompareBytes( dataBlock.data, "SPR", 3 ) )
    {
        return TYPE_SPR;
    }
    else if( CompareBytes( dataBlock.data, "ANI", 3 ) )
    {
        return TYPE_ANI;
    }
    else if( CompareBytes( dataBlock.data, "COL", 3 ) )
    {
        return TYPE_COL;
    }
    else
    {
        return TYPE_UNK;
    }
    #pragma GCC diagnostic pop
    return -1;
}
bool NGRCreator::CompareBytes( char* a, char* b, unsigned int length )
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
void NGRCreator::OpenFile()
{

    ClearTreeView();
    auto dialog = new Gtk::FileChooserDialog( "Please select Files", Gtk::FileChooser::Action::OPEN );
    dialog->set_transient_for( *this );
    dialog->set_select_multiple( false );

    //Add response buttons the the dialog:
    dialog->add_button( "Cancel", Gtk::ResponseType::CANCEL );
    dialog->add_button( "Select", Gtk::ResponseType::OK );
    dialog->signal_response().connect( sigc::bind( sigc::mem_fun( *this, &NGRCreator::OnOpenFileDialogResponse ), dialog ) );
}
void NGRCreator::OnOpenFileDialogResponse( int response_id, Gtk::FileChooserDialog* dialog )
{
    //Handle the response:
    switch ( response_id )
    {
        case Gtk::ResponseType::OK:
        {
            vector<string> files = dialog->get_filenames();
            if( files.size() > 0 )
            {
                ReadNGRFile( files[0] );
            }
            break;
        }
        case Gtk::ResponseType::CANCEL:
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

    delete dialog;
}
void NGRCreator::ReadNGRFile( string filename )
{
    cout<<"opening file..."<<endl;

    FreeAllDataBlocks();
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
void NGRCreator::FreeAllDataBlocks()
{
    for( unsigned int i = 0; i < data.size(); i++ )
    {
        free( data[i].data );
    }
    data.clear();
}
void NGRCreator::Save()
{
    auto dialog = new Gtk::FileChooserDialog( "Please select Files", Gtk::FileChooser::Action::SAVE );
    dialog->set_transient_for( *this );
    dialog->set_select_multiple( false );

    //Add response buttons the the dialog:
    dialog->add_button( "Cancel", Gtk::ResponseType::CANCEL );
    dialog->add_button( "Select", Gtk::ResponseType::OK );
    dialog->signal_response().connect( sigc::bind( sigc::mem_fun( *this, &NGRCreator::OnSaveFileDialogResponse ), dialog ) );
}
void NGRCreator::OnSaveFileDialogResponse( int response_id, Gtk::FileChooserDialog* dialog )
{
    //Handle the response:
    switch ( response_id )
    {
        case Gtk::ResponseType::OK:
        {
            vector<string> files = dialog->get_filenames();

            if( files.size() > 0 )
            {
                SaveDataToFile( files[0] );
            }
            break;
        }
        case Gtk::ResponseType::CANCEL:
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

    delete dialog;
}
void NGRCreator::SaveDataToFile( string filepath )
{
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
void NGRCreator::NewFile()
{
    freeAllDataBlocks();
    ClearTreeView();
}
void NGRCreator::freeAllDataBlocks()
{
    for( unsigned int i = 0; i < data.size(); i++ )
    {
        free( data[i].data );
    }
    data.clear();
}
void NGRCreator::RemoveItems()
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
void NGRCreator::SelectedRowCallback( const Gtk::TreeModel::iterator& iter )
{
    Gtk::TreeModel::Row row = *iter;
    cout<<row[columns.index]<<endl;
}

void NGRCreator::SelectionChanged()
{
    cout<<"changed";
}

void NGRCreator::CellsEdited( string path, string newText )
{
    int editIndex = atoi(path.c_str());
    cout<<editIndex<<", "<<newText<<endl;
    data[editIndex].name = newText;
    ClearTreeView();
    AddAllDataBlocksToTreeView();
}











int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create("org.gtkmm.example");

    //Shows the window and returns when it is closed.
    return app->make_window_and_run<NGRCreator>(argc, argv);
}
