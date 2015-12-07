#include "DrawerVisitor.h"

DrawerVisitor::DrawerVisitor(QGraphicsScene* scene, QWidget *widget)
{
    //ctor
    this->widget = widget;
    this->scene = scene;
}

DrawerVisitor::~DrawerVisitor()
{
    //dtor
}
void DrawerVisitor::visitSimpleGraphics(SimpleGraphics *sg) {
    //do

    int x,y,w,l;



    const char *temp = sg->shape()->describe().c_str();
    switch(temp[0]){
    case 'C':{
        char *dst = new char [sg->shape()->describe().size()+1];
        strcpy(dst,sg->shape()->describe().c_str());
        char *data = strtok(dst,"(");
        data=strtok(NULL,"(");
        data=strtok(data,")");
        char *para1,*para2,*para3;
        para1=strtok(data,",");
        para2=strtok(NULL,",");
        para3=strtok(NULL,",");
        int p1,p2,p3;
        p1=atoi(para1);
        p2=atoi(para2);
        p3=atoi(para3);
        display(p1,p2,p3,0,sg);
        }
        break;
    case 'S':
        x=sg->getBoundingBox().llx();
        y=sg->getBoundingBox().lly();
        w=sg->getBoundingBox().urx()-x;
        l=sg->getBoundingBox().ury()-y;

        display(x,y,w,l,0,sg);
        break;
    case 'R':
        x=sg->getBoundingBox().llx();
        y=sg->getBoundingBox().lly();
        w=sg->getBoundingBox().urx()-x;
        l=sg->getBoundingBox().ury()-y;

        display(x,y,w,l,0,sg);
        break;
    }

}
void DrawerVisitor::visitCompositeGraphics (CompositeGraphics *cg) {
    parent = NULL;
    int x,y,w,l;
    x=cg->getBoundingBox().llx();
    y=cg->getBoundingBox().lly();
    w=cg->getBoundingBox().urx()-x;
    l=cg->getBoundingBox().ury()-y;
//    x*=100;
//    y*=100;
//    w*=100;
//    l*=100;
    int type=1;
    display(x,y,w,l,type,cg);
}

void DrawerVisitor::display(int x, int y,int w, int l, int type, Graphics * g){
    Painter *item = new Painter(x, y, w, l, this->widget, g, scene, type);
    setting(item,type);
}

void DrawerVisitor::display(int x, int y,int r, int type, Graphics * g){
    Painter *item = new Painter(x, y, r, this->widget, true, g, scene, type);
    setting(item,type);
}
void DrawerVisitor::setting(Painter *item, int type){
    cout<<"type:"<<type<<endl;
    if(type==0)
        item->setColor(0);
    else{
        item->setColor(1);
        parent = item;
        cout<<"parent->"<<item<<endl;
    }
    if(type==0&&parent!=NULL){
        cout<<"set parent"<<endl;
        item->setParentItem(parent);
        cout<<"sizeee:"<<parent->childItems().size()<<endl;
        cout<<"parent:"<<item->parentItem()<<endl;
    }
    if(parent==NULL){
        this->scene->addItem(item);
        cout<<"add child"<<endl;
    }
    else if(type==1){
        this->scene->addItem(parent);
//        new QGraphicsItem()->setParentItem(parent);
        cout<<"child items"<<parent->childItems().size()<<endl;
        cout<<"add parent"<<endl;
    }
}
