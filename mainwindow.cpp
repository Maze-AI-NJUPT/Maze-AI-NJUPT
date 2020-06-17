#include "mainwindow.h"
#include <QMessageBox>
#include <QStyleFactory>
#include <QPalette>
#include <QPixmap>
#include <QTime>

int MainWindow::bushu = 0;




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉边框
    initialWindow_Layout();
    //初始化时间种子
    QTime time=QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);

    MainWindow::bushu = 0;
}

MainWindow::~MainWindow()
{
}


void MainWindow::initialWindow_Layout()
{
    gLayout_Map=new QGridLayout;
    hLayout=new QHBoxLayout;
    gLayout_Map->setContentsMargins(0,0,0,0);//让布局紧贴主窗口，不留空白
    gLayout_Map->setSpacing(0);//让两个控件之间的间隔为0
    hLayout->setContentsMargins(0,0,0,0);
    hLayout->setSpacing(0);
    //初始化迷宫砖块
    for(int i=0; i <60 ;i++)
    {
        for(int j=0; j<60; j++)
        {
            MazeWidget[i][j]=new QWidget(this);
            gLayout_Map->addWidget(MazeWidget[i][j],i,j);
            MazeWidget[i][j]->hide();
        }
    }
    //初始化角色
    People=new QWidget(this);
    People->hide();

    QWidget *Mapwidget=new QWidget(this);

    surface=new interface(this);
    surface->setMinimumSize(840,680);
    connect(surface->timer,SIGNAL(timeout()),this,SLOT(ShowWidget()));//显示控制界面()));//传递过来的参数有问题，会一直调用槽函数
    gLayout_Map->addWidget(surface,0,0);
    Mapwidget->setMinimumSize(840,680);
    Mapwidget->setLayout(gLayout_Map);

    BASIC_WIDTH=0;
    BASIC_HEIGHT=0;
    iNum=0;
    lastheight=0;
    lastwidth=0;
    isPlay=false;
    isShow=false;
    issurface=true;
    isAIAnimationButton=false;
    isAutoMoveButton=false;
    display_it=0;

    initialControlWidget();

    MainWidget=new QWidget(this);
    hLayout->addWidget(Mapwidget);
    hLayout->addWidget(Controlwidget);

    MainWidget->setLayout(hLayout);
    MainWidget->setFocusPolicy(Qt::StrongFocus);

    //设置widget为Mainwindow的中心窗口
    this->setCentralWidget(MainWidget);
    group=new QSequentialAnimationGroup;
    timer=new QTimer(this);
    iNum=1;

    connect(timer,SIGNAL(timeout()),this,SLOT(moveCharacter()));
    connect(timer,SIGNAL(timeout()),this,SLOT(ShowPath()));

    BGM=new QMediaPlayer(this);//背景音乐
    BGM->setMedia(QUrl("qrc:/music/music/main_theme.mp3"));//相对路径
    BGM->setVolume(50);


}

void MainWindow::initialControlWidget()
{
    gLayout_Control=new QGridLayout;
    gLayout_Control->setSpacing(10);
    Controlwidget=new QWidget(this);
    Controlwidget->setStyleSheet("background-color:lightGray");
    QString button_style="QPushButton{background-color:white; color: black;border-radius:1px;border:2px groove gray;border-style:outset;}"
                         "QPushButton:hover{background-color:lightGray; color: black;}"
                         "QPushButton:pressed{background-color:gray;border-style:inset;}";

   QLabel *label_w=new QLabel;
    QLabel *label_h=new QLabel;
     QLabel *label_bs=new QLabel;
    label_bsc = new QLabel;

    label_w->setStyleSheet("background-color:transparent");
    label_h->setStyleSheet("background-color:transparent");
    label_bs->setStyleSheet("background-color:transparent");
    label_bsc->setStyleSheet("background-color:transparent");
    QLabel *label_blank[10];
    for(int i=0;i<10;i++)
    {
        label_blank[i]=new QLabel(this);
        label_blank[i]->setStyleSheet("background-color:transparent");
    }

    label_Stytle=new QLabel;
    StytleNum=2;
    label_Stytle->setStyleSheet(m.MapStytle[StytleNum][15]);

    QLabel *label_select=new QLabel;

    label_w->setText("迷宫宽度");
    label_h->setText("迷宫高度");
    label_bs->setText("当前已走步数：");
    label_bsc->setText("0");
    label_select->setText("选择人物");
    sp_w=new QSpinBox(this);
    sp_h=new QSpinBox(this);


    sp_w->setStyleSheet("background-color:transparent");
    sp_h->setStyleSheet("background-color:transparent");
    SelectMapStytle=new QComboBox(this);
    SelectMapStytle->addItem(tr("孙悟空"));//项目编号从0开始
    SelectMapStytle->addItem(tr("猪八戒"));
    SelectMapStytle->addItem(tr("唐僧"));
    SelectMapStytle->setCurrentIndex(2);
    connect(SelectMapStytle,SIGNAL(currentIndexChanged(int)),this,SLOT(MapStytleSet()));
    //currentIndexChanged(int) 中的int 去掉，就不能被识别为信号

    //按钮初始化
    QPushButton *GenerateButton=new QPushButton(this);
    quitButton=new QPushButton(this);
    AIAnimationButton=new QPushButton(this);
    AutoMoveButton=new QPushButton(this);

    // 单选按钮
    radio[0] = new QRadioButton("深度优先",this);
    radio[0]->setChecked(true);
    radio[1] = new QRadioButton("广度优先",this);
    radio[2] = new QRadioButton("QLearning",this);
    radio_group = new QButtonGroup(this);
    radio_group->addButton(radio[0]);
    radio_group->addButton(radio[1]);
    radio_group->addButton(radio[2]);
    not_bestPath_check = new QCheckBox("显示寻路过程",this);
    not_bestPath_check->setChecked(true);
    AIAnimationButton->setEnabled(false);
    AutoMoveButton->setEnabled(false);

    GenerateButton->setText("生成迷宫");
    AutoMoveButton->setText("寻路路径");
    AIAnimationButton->setText("AI操作");
    quitButton->setText("主菜单");
    quitButton->setEnabled(false);
    GenerateButton->setStyleSheet(button_style);
    AutoMoveButton->setStyleSheet(button_style);

    AIAnimationButton->setStyleSheet(button_style);
    quitButton->setStyleSheet(button_style);

    connect(GenerateButton,SIGNAL(clicked()),this,SLOT(CreateMaze_Layout()));
    connect(AutoMoveButton,SIGNAL(clicked()),this,SLOT(timeStart()));


    connect(AIAnimationButton,SIGNAL(clicked()),this,SLOT(ShowAnimation()));
    connect(quitButton,SIGNAL(clicked()),this,SLOT(quit()));

    gLayout_Control->addWidget(label_w,0,0);
    gLayout_Control->addWidget(label_h,1,0);
    gLayout_Control->addWidget(label_bs,2,0);
    gLayout_Control->addWidget(label_bsc,2,1);
    gLayout_Control->addWidget(label_blank[0],0,3);

    gLayout_Control->addWidget(sp_w,0,1);
    gLayout_Control->addWidget(label_blank[1],1,2);

    gLayout_Control->addWidget(sp_h,1,1);
    gLayout_Control->addWidget(label_blank[2],2,0,1,3);

    gLayout_Control->addWidget(label_select,3,0);
    gLayout_Control->addWidget(label_blank[3],3,2);

    gLayout_Control->addWidget(SelectMapStytle,3,1);
    gLayout_Control->addWidget(label_Stytle,4,0,1,2);

    gLayout_Control->addWidget(GenerateButton,5,0);
    gLayout_Control->addWidget(not_bestPath_check,5,1);
    gLayout_Control->addWidget(radio[0],6,0);
    gLayout_Control->addWidget(radio[1],6,1);
    gLayout_Control->addWidget(radio[2],6,2);
    gLayout_Control->addWidget(AutoMoveButton,8,0);

    gLayout_Control->addWidget(AIAnimationButton,8,1);

    gLayout_Control->addWidget(quitButton,9,1);
    Controlwidget->setLayout(gLayout_Control);
    Controlwidget->hide();
}
void MainWindow::resetMaze()
{
    AIAnimationButton->setEnabled(false);
    AutoMoveButton->setEnabled(false);

    sp_h->setValue(0);
    sp_w->setValue(0);

    SelectMapStytle->setCurrentIndex(2);
}

QString intToQString(int num)
{
    QString result="";
    result.sprintf("%d",num);
    return result;
}

bool isOdd(int num)
{
    return !(num%2==0);
}


void MainWindow::CreateMaze_Layout()
{
    //停止之前可能的工作
    MainWindow::bushu = 0;
    timer->stop();
    group->stop();
    iNum=1;
    MainWindow::label_bsc->setText(intToQString(0));

    if((sp_h->value()<7||sp_h->value()>100)||(sp_w->value()<7||sp_w->value()>100))
    {
        QMessageBox message(QMessageBox::NoIcon, "警告！", "输入的数据需在7-100之间");
        message.setIconPixmap(QPixmap(":/info/image/information/warning.png"));
        message.exec();
        return;
    }
    else
    {
        m.row=sp_h->value();
        m.col=sp_w->value();
    }
    //当h和w都为偶数时，迷宫的出口（row-2，col-2）会被墙给封住
    if(!isOdd(m.row)&&!isOdd(m.col))
    {
        if(m.row>m.col)
        {
            m.row+=1;
            m.col=m.row;
        }
        else
        {
            m.col+=1;
            m.row=m.col;
        }
    }
    BASIC_WIDTH=840/m.col;//52
    BASIC_HEIGHT=680/m.row;//56

    if(issurface)
    {
        surface->hide();
        gLayout_Map->removeWidget(surface);
        issurface=false;
    }

    People->setMinimumSize(BASIC_WIDTH,BASIC_HEIGHT);

    int temph=m.getRow();
    int tempw=m.getCol();
    m.initialMaze(temph,tempw);
    m.genMap();
    m.setCharacterPos();
    //m.setExitPos();


    StytleNum=SelectMapStytle->currentIndex();
    ShowMaze_Layout();
    lastheight=temph;
    lastwidth=tempw;
    //m.last_row=m.row;

    AIAnimationButton->setEnabled(true);
    AutoMoveButton->setEnabled(true);

    quitButton->setEnabled(true);
    isPlay=true;
}

//布局管理器方式，大小可以随着窗口改变
void MainWindow::ShowMaze_Layout()
{
    if(isShow)
    {
        for(int i=0;i<lastheight;i++)
        {
            for(int j=0;j<lastwidth;j++)
            {
                MazeWidget[i][j]->hide();
            }
        }
    }
    gLayout_Map->addWidget(People,m.gamer.first,m.gamer.second);
    People->setStyleSheet(m.MapStytle[StytleNum][0]);
    People->show();//用就显示
    for(int i=0;i<m.row;i++)
    {
        for(int j=0;j<m.col;j++)
        {
            MazeWidget[i][j]->setMinimumSize(BASIC_WIDTH,BASIC_HEIGHT);
            MazeWidget[i][j]->show();//要用的窗口必须要显示出来
            if(m.game_map[i][j].getType()== WALL)//状态0 代表 墙 障碍
                MazeWidget[i][j]->setStyleSheet(m.MapStytle[StytleNum][12]);
            if(m.game_map[i][j].getType()== ROAD)//状态1 代表 草地 非障碍
                MazeWidget[i][j]->setStyleSheet(m.MapStytle[StytleNum][13]);
        }
    }
    MazeWidget[m.end.first][m.end.second]->setStyleSheet(m.MapStytle[StytleNum][14]);
    isShow=true;
}
void MainWindow::hideMaze()
{

    for(int i=0;i<lastheight;i++)
    {
        for(int j=0;j<lastwidth;j++)
        {
            MazeWidget[i][j]->hide();
        }
    }
    People->hide();
    isShow=false;
    surface->classicalisok=false;
}
void MainWindow::quit()
{
    Controlwidget->hide();
    hideMaze();
    resetMaze();
    surface->isok=false;

    surface->show();//开始界面显示后，主窗口大小还是不变
    this->resize(840,680);//需要重新设置主窗口大小

    surface->showMianMenu();
    issurface=true;//标识主界面显示过
}


//角色跳跃方式移动(结合布局管理器)
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(surface->classicalisok)//经典模式
    {
        //qDebug()<<"Key is active!";
        if(!isPlay)
        {
            return;
        }
        int step=0;
        //可以作为调节速度的接口
        //while(step<100000000)
        while(step<1000)
        {
           step++;
        }
        switch(event->key())
        {
        case Qt::Key_W://上
            //上面为墙，则什么也不执行
            if(m.game_map[m.gamer.first-1][m.gamer.second].getType()==WALL)
            {
                return;
            }
            MainWindow::bushu+=1;
            m.gamer.first-=1;
            qDebug()<<MainWindow::bushu;

            gLayout_Map->addWidget(People,m.gamer.first,m.gamer.second);
            People->setStyleSheet(m.MapStytle[StytleNum][3]);//显示向上移动图片
            break;
        case Qt::Key_S://下
            if(m.game_map[m.gamer.first+1][m.gamer.second].getType()==WALL)
            {
               return;
            }
            MainWindow::bushu+=1;
            m.gamer.first+=1;
            qDebug()<<MainWindow::bushu;

            gLayout_Map->addWidget(People,m.gamer.first,m.gamer.second);
            People->setStyleSheet(m.MapStytle[StytleNum][0]);
            break;
        case Qt::Key_A://左
            if(m.game_map[m.gamer.first][m.gamer.second-1].getType()==WALL)
            {
                return;
            }
            MainWindow::bushu+=1;
            m.gamer.second-=1;
            qDebug()<<MainWindow::bushu;

            gLayout_Map->addWidget(People,m.gamer.first,m.gamer.second);
            People->setStyleSheet(m.MapStytle[StytleNum][6]);
            //qDebug()<<"col "<<People->col()<<"row "<<People->row();
            break;
        case Qt::Key_D://右
            if(m.game_map[m.gamer.first][m.gamer.second+1].getType()==WALL)
            {
                return;
            }
            MainWindow::bushu+=1;
            m.gamer.second+=1;
            qDebug()<<MainWindow::bushu;

            gLayout_Map->addWidget(People,m.gamer.first,m.gamer.second);
            People->setStyleSheet(m.MapStytle[StytleNum][9]);
            break;
        }
        if(m.gamer.first==m.end.first&&m.gamer.second==m.end.second)
        {
            QMessageBox message(QMessageBox::NoIcon, "取经人", "继续向下走吧！");
            //bushu->setText(intToQString(bushu));
            message.setIconPixmap(QPixmap(":/info/image/information/congratulation.png"));
            message.exec();//不加这个对话框会一闪而过
            CreateMaze_Layout();
            return;
        }
        MainWindow::label_bsc->setText(intToQString(MainWindow::bushu));
    }
    else
    {
        return;
    }
}

//重写鼠标点击和移动事件，使没有边框的窗口可以通过鼠标移动
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    this->windowPos = this->pos();                // 获得部件当前位置
    this->mousePos = event->globalPos();     // 获得鼠标位置
    this->dPos = mousePos - windowPos;       // 移动后部件所在的位置
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    this->move(event->globalPos() - this->dPos);
}

void MainWindow::ShowAnimation()
{
    int option =0;
    if(!not_bestPath_check->isChecked())
        option = 2;
    if(radio[0]->isChecked())
        ai = new Dfs(m,option);
    else if(radio[1]->isChecked())
        ai = new Bfs(m,option);
    else
        ai = new QLearning(m,0,option);
    ai->solve();
#if debug_QLearning
    ai->m.printValue();
#endif
    group->clear();//动画组清空
    isAIAnimationButton=true;
    isAutoMoveButton=false;
    AutoMoveButton->setEnabled(false);
    for(int i=0; i<ai->ans.size()-1;i++)
    {
        QPropertyAnimation* animation = new QPropertyAnimation(People, "pos");//动作初始化,People是操作对象
        animation->setDuration(200);//设置动作间隔                              //"pos"是操作属性，与QPoint 对应
                                                                              //"geometry" 与QRect/QRectF 对应
        animation->setStartValue(QPoint(ai->ans[i].first.second*BASIC_WIDTH,ai->ans[i].first.first*BASIC_HEIGHT));
        animation->setEndValue(QPoint(ai->ans[i+1].first.second*BASIC_WIDTH,ai->ans[i+1].first.first*BASIC_HEIGHT));
        animation->setEasingCurve(QEasingCurve::Linear);
        group->addAnimation(animation);//向动画组中添加动作
    }
    timer->start(200);//设置计时间隔，必须与动作间隔大小一样，才会同步
    group->start();//动画组启用
}

void MainWindow::timeStart()
{
    int option = 1;
    if(!not_bestPath_check->isChecked())
        option = 2;
    if(radio[0]->isChecked())
        ai = new Dfs(m,option);
    else if(radio[1]->isChecked())
        ai = new Bfs(m,option);
    else
        ai = new QLearning(m,0,option);
    ai->solve();
#if debug_QLearning
    ai->m.printValue();
#endif

    isAutoMoveButton=true;
    isAIAnimationButton=false;
    AIAnimationButton->setEnabled(false);
    timer->start(50);
}
void MainWindow::MapStytleSet()
{
   label_Stytle->setStyleSheet(m.MapStytle[SelectMapStytle->currentIndex()][15]);

}
void MainWindow::ShowWidget()
{
    if(surface->isok)
    {
        if(surface->classicalisok)
        {
            Controlwidget->show();
        }
    }
}

void MainWindow::ShowPath()
{
    if(!isAIAnimationButton)
    {
        auto temp=ai->ans[iNum];
        MazeWidget[temp.first.first][temp.first.second]->setStyleSheet(m.MapStytle[StytleNum][0]);
        iNum++;
        if(iNum == ai->ans.size()-1)
        {
            iNum = 0;
            for(int i=0;i<ai->ans.size();i++)
            {
                auto temp=ai->ans[i];
                MazeWidget[temp.first.first][temp.first.second]->setStyleSheet(m.MapStytle[StytleNum][13]);
                MazeWidget[m.row-2][m.col-2]->setStyleSheet(m.MapStytle[StytleNum][14]);
            }
            timer->stop();
            AIAnimationButton->setEnabled(true);
            isAutoMoveButton=false;
            isAIAnimationButton=false;
            return;
        }

    }
}
void MainWindow::moveCharacter()//设置移动时的图片
{
    if(!isAutoMoveButton)
    {
        if(ai->ans[iNum].second == UP)//up
        {
            People->setStyleSheet(m.MapStytle[StytleNum][3+iNum%3]);
        }
        if(ai->ans[iNum].second == DOWN)//down
        {
            People->setStyleSheet(m.MapStytle[StytleNum][0+iNum%3]);
        }
        if(ai->ans[iNum].second == RIGHT)//right
        {
            People->setStyleSheet(m.MapStytle[StytleNum][9+iNum%3]);
        }
        if(ai->ans[iNum].second == LEFT)//left
        {
            People->setStyleSheet(m.MapStytle[StytleNum][6+iNum%3]);
        }
        iNum++;
        if(iNum == ai->ans.size()-1)
        {
            timer->stop();
            iNum = 0;
            AutoMoveButton->setEnabled(true);
            return;
        }
    }

}
