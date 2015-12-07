#include "gui.moc"
gui::gui()
{
//    ctor
    CreateView();
    CreateActions();
    CreateMenus();
    SetActionConnection();
    QString title = "104598057";
    setWindowTitle(title);
    setMinimumSize(800, 600);
    setMaximumSize(800, 600);
    //Display();

}

gui::~gui()
{
    delete widget;
    delete scene;
    //dtor
}

void gui::CreateView(){
    widget = new QWidget();//繪製painter item的物件
    setCentralWidget(widget);
    graphicsView = new QGraphicsView(widget);//要調整生成的位置
    QString gView = "graphicView";
    graphicsView->setObjectName(gView);


    toolBar = addToolBar("File");
    toolBar->addSeparator();

    scene = new QGraphicsScene();//管理painter item的物件
    graphicsView->setScene(scene);
    QVBoxLayout *layout = new QVBoxLayout;//呈現畫面
    layout->setMargin(0);
    layout->addWidget(graphicsView);
    widget->setLayout(layout);
}

void gui::SetActionConnection() {
    connect(fileLoad_tool, SIGNAL(triggered()), this, SLOT(LoadFile()));
    connect(fileSave_tool, SIGNAL(triggered()), this, SLOT(SaveFile()));
    connect(newCir, SIGNAL(triggered()), this, SLOT(CreateCircle()));
    connect(newRec, SIGNAL(triggered()), this, SLOT(CreateRectangle()));
    connect(newSqu, SIGNAL(triggered()), this, SLOT(CreateSquare()));
    connect(removeItem, SIGNAL(triggered()), this, SLOT(Remove()));
    connect(lock, SIGNAL(triggered()), this, SLOT(Group()));
    connect(unlock, SIGNAL(triggered()), this, SLOT(UnGroup()));

    connect(aboutDeveloper, SIGNAL(triggered()), this, SLOT(MessageDialog()));
    connect(fileLoad, SIGNAL(triggered()), this, SLOT(LoadFile()));
    connect(fileSave, SIGNAL(triggered()), this, SLOT(SaveFile()));
    connect(createSquare, SIGNAL(triggered()), this, SLOT(CreateSquare()));
    connect(createRectangle, SIGNAL(triggered()), this, SLOT(CreateRectangle()));
    connect(createCircle, SIGNAL(triggered()), this, SLOT(CreateCircle()));
}

void gui::CreateSquare(){
    int level = 0;
    string square = "S(100,100,100)";
    gs.push_back(gf.extractGraphicsFromOneLine(square,level,gf.itemID));
    drawOnCanvas();
}

void gui::CreateRectangle(){
    int level = 0;
    string rec = "R(100,100,100,150)";
    gs.push_back(gf.extractGraphicsFromOneLine(rec,level,gf.itemID));
    drawOnCanvas();
}

void gui::CreateCircle(){
    int level = 0;
    string cir = "C(100,100,100)";
    gs.push_back(gf.extractGraphicsFromOneLine(cir,level,gf.itemID));
    drawOnCanvas();
}

void gui::CreateActions() {
    QPixmap savePic("save.png");
    QPixmap loadPic("load.png");
    QPixmap cirPic("cir.png");
    QPixmap recPic("rec.png");
    QPixmap squPic("squ.png");
    QPixmap prePic("pre.png");
    QPixmap postPic("post.png");
    QPixmap removePic("remove.png");
    QPixmap lockPic("lock.png");
    QPixmap unlockPic("unlock.png");

    fileLoad_tool = toolBar->addAction(QIcon(loadPic), "Load");
    fileSave_tool = toolBar->addAction(QIcon(savePic), "Save");
    newCir = toolBar->addAction(QIcon(cirPic), "new Circle");
    newRec = toolBar->addAction(QIcon(recPic), "new Rectangle");
    newSqu = toolBar->addAction(QIcon(squPic), "new Square");
    undo = toolBar->addAction(QIcon(prePic), "undo");
    redo = toolBar->addAction(QIcon(postPic), "redo");
    removeItem = toolBar->addAction(QIcon(removePic), "remove");
    lock = toolBar->addAction(QIcon(lockPic), "lock");
    unlock = toolBar->addAction(QIcon(unlockPic), "unlock");

    aboutDeveloper = new QAction("aboutDeveloper", widget);
    fileLoad = new QAction("fileLoad", widget);
    fileSave = new QAction("fileSave", widget);
    createSquare = new QAction("createSquare", widget);
    createRectangle = new QAction("createRectangle", widget);
    createCircle = new QAction("createCircle", widget);
}

void gui::CreateMenus() {
     file = menuBar()->addMenu("File");
     file->addAction(fileLoad);
     file->addAction(fileSave);
     about = menuBar()->addMenu("About");
     about->addAction(aboutDeveloper);
     createShape = menuBar()->addMenu("createShape");
     createShape->addAction(createSquare);
     createShape->addAction(createRectangle);
     createShape->addAction(createCircle);
}
void gui::Display() {
//    Painter *item = new Painter(100,100, 200, 100, widget);
//    scene->addItem(item);
//    scene->update();
}

void gui::Group(){
    //scene->createItemGroup();
    int level = 0;
    string comp = string("Comp R(0,0,0,0)");
    gf.pda.push(std::make_pair(0,gf.extractGraphicsFromOneLine(comp, level, gf.itemID)));
    for(auto e:scene->selectedItems()){
        for(int i=0;i<gs.size();i++){
            if(gs[i]->getID()==e->data(0)){
                gf.pda.push(std::make_pair(1,gs[i]));
                gs.erase(gs.begin()+i);
            }
        }
    }
    gf.compose();
    gs.push_back(gf.pda.top().second);
    drawOnCanvas();
}

void gui::UnGroup(){
    cout<<gs.size()<<":";
    for(auto x:gs){
        cout<<x->getID()<<"~";
    }
    for(auto e:scene->selectedItems()){
        for(int i=0;i<gs.size();i++){
            if(gs[i]->getID()==e->data(0)){
                for(auto x:gs[i]->getObj())
                    gs.push_back(x);
                gs.erase(gs.begin()+i);
            }
        }
    }
    cout<<gs.size()<<":";
    for(auto x:gs){
        cout<<x->getID()<<"~";
    }
    drawOnCanvas();
}

void gui::Remove(){
    for(auto e:scene->selectedItems()){

        for(int i=0;i<gs.size();i++){
            if(gs[i]->getID()==e->data(0))
                gs.erase(gs.begin()+i);
        }
    }
    drawOnCanvas();
}

void gui::MessageDialog() {
    QMessageBox msgbox;
    std::string message("104598057\n");
    message += std::string("author:tonyHsu\n");
    QString qstr = QString::fromStdString(message);
    msgbox.setText(qstr);
    msgbox.exec();
}

void gui::LoadFile(){
    QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.txt)"));
    if(path.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    } else {
        cout<<"load done";
        const char *fileName = path.toStdString().c_str();
        cout<<fileName<<"!"<<endl;
        for(auto e:gf.buildGraphicsFromFile(fileName))
            gs.push_back(e);

        drawOnCanvas();
    }
}

void gui::drawOnCanvas(){
    scene->clear();
    DrawerVisitor dv(scene, widget);
    DescriptionVisitor ds;
    for( auto e:gs ){
        ds.clear();
        e->accept(dv);
        e->accept(ds);
        cout<<"e:"<<e->getID()<<" "<<ds.getDescription();
    }
    scene->update();
}

void gui::SaveFile(){
    DescriptionVisitor ds;
    for( auto e:gs )
        e->accept(ds);
    save(ds.getDescription());
}

void gui::save(string s)
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save Image"), ".", tr("Image Files(*.txt)"));
    QString text = QString::fromStdString(s);
    QFile f( path );
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)){
        cout<<"open file failed";
        return;
    }
    QTextStream t( &f );
    t << text;
    f.close();
    cout<<"write success";
   // statusBar()->message( QString( "File %1 saved" ).arg( "out.txt" ), 2000 );
}

