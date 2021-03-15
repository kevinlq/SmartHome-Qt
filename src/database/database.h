/***************************************************************
 *Copyright(c) 2014-2015 Company By LH Unigress
 *All rights reserved.
 *文件名称：数据库的创建文件
 *简要描述：创建数据库，数据表
 *
 *当前版本：V2.0
 *作者：Kelvin Li
 *创作日期：2014/10
 *说明：
*****************************************************************/
#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QtSql>
#include <QObject>


/*创建数据里并链接*/
static bool createConnection()
{
    QSqlDatabase db;            //创建一个数据库
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        db = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
    }
    db.setHostName("localhost");
    db.setDatabaseName("SmartHome.db");  //设置数据库的名字
    db.setUserName("root");
    db.setPassword("123456");
    if(!db.open())
    {
        qCritical("Can't open database: %s(%s)",
                  db.lastError().text().toLocal8Bit().data(),
                  qt_error_string().toLocal8Bit().data());

        return false;
    }

 #if 0
    QSqlQuery query;
    /***************************用 户  表 ****************************
     *用户账号、用户姓名、用户密码、用户类型（管理员/售货员）
    */
    query.exec(QObject::tr("create table UserInfo (UserId vchar(4) primary key not null,"
                           "UserName vchar(10),UserPwd vchar(10),UserType vchar(20))"));
    query.exec(QObject::tr("insert into UserInfo values ('1001','admin','admin','管理员')"));
    query.exec(QObject::tr("insert into UserInfo values ('1002','小刘','admin','售货员')"));


    /*
     *商品入库表
     *库存编号、商品编码、库存数量
    */
    query.exec(QObject::tr("create table Store (StoreId vchar(8) PRIMARY KEY NOT NULL,"
                           "StoreName vchar(10) NOT NULL,"
                           "StoryNum Int(4) NOT NULL CHECK(StoryNum>=0))"));

    /**********************会 员 卡 信 息 表********************/
    query.exec(QObject::tr("create table Member(MemberId NUMERIC(9) PRIMARY KEY"
                           "CONSTRAINT C1 CHECK(MemberId BETWEEN 80000000 AND 99999999),"
                           "MemberName vchar(10),MemberPhone vchar(11) NOT NULL,"
                           "MemberAddress vchar(100),MemberClass vchar(10),"
                           "MemberGrade vchar(20) ,MemberCost vchar(20),"
                           "MemberRegister vchar(20),MemberBirthday vchar(20),"
                           "MemberEmail vchar(20),CurrentTime vchar(30),"
                           "MemberRemark vchar(500))"));
    query.exec(QObject::tr("insert into Member values (80000000,'xx1','15383463513',"
                           "'xxx工业学院','普通级','300','350',"
                           "'2014-08-20','1992-01-01','Zhang@163.com','','')"));
    query.exec(QObject::tr("insert into Member values (80000001,'xx2','15383465641',"
                           "'xxx工业学院','尊贵级','3000','10000',"
                           "'2014-06-20','1992-11-24','creazylq@163.com','','')"));
    query.exec(QObject::tr("insert into Member values (80000002,'xx3','15388511234',"
                           "'xxx工业学院','普通级','440','500',"
                           "'2013-06-20','1991-1-4','zhangzj@163.com','','')"));
    query.exec(QObject::tr("insert into Member values (80000003,'xx4','15388513945',"
                           "'xxx工业学院','尊贵级','1000','1200',"
                           "'2011-04-12','1992-4-12','meixiang@163.com','','')"));
    query.exec(QObject::tr("insert into Member values (80000004,'xx5','15388513920',"
                           "'xxx工业学院','普通级','500','700',"
                           "'2001-06-20','1991-3-2','maendong@163.com','','')"));
    query.exec(QObject::tr("insert into Member values (80000005,'xx6','15388510110',"
                           "'xxx工业学院','普通级','500','700',"
                           "'2014-09-10','1991-8-2','guzhongxin@163.com','','')"));

    /**********************商 品 信 息 表********************************
     *商品编号、库存号(外键)、商品名称、供货商号(外键)、商品类型、价格（不能<0）
    */
    query.exec(QObject::tr("CREATE TABLE GoodsInfo(GoodsId vchar(8) PRIMARY KEY NOT NULL,"
                           "StoreId vchar(8) NOT NULL,GoodsName vchar(10)NOT NULL,"
                           "SupplyId vchar(8) NOT NULL,GoodsType vchar(10)NOT NULL,"
                           "GoodsPrice int(4) NOT NULL CHECK (GoodsPrice >0),"
                           "FOREIGN KEY(StoreId) REFERENCES Store(StoreId),"
                           "FOREIGN KEY(SupplyId) REFERENCES Supply(SupplyId))"));

    /**********************供 货 商 表***********************************
     *供货商ID、姓名、地址、电话
    */
    query.exec(QObject::tr("create table Supply(SupplyID vchar(8)PRIMARY KEY NOT NULL,"
                           "SupplyName vchar(10)NOT NULL,SupplyAdress vchar(50)NOT NULL,"
                           "SupplyPhone vchar(11) NOT NULL)"));

    /***********************生产厂商表******************************
     *生产商编号、姓名、地址、电话
    */
    query.exec(QObject::tr("create table Product(ProductId vchar(8)PRIMARY KEY NOT NULL,"
                           "ProductName vchar(40)NOT NULL,"
                           "ProductAddress vchar(40),ProductPhone vchar(20))"));


    /**************************商品颜色表*******************************
     *颜色编号、名称
    */
    query.exec(QObject::tr("create table Color(ColorId vchar(4) PRIMARY KEY NOT NULL,"
                           "ColorKind vchar(10))"));
    query.exec(QObject::tr("insert into Color values ('01','透明')"));
    query.exec(QObject::tr("insert into Color values ('02','红色')"));
    query.exec(QObject::tr("insert into Color values ('03','橙色')"));
    query.exec(QObject::tr("insert into Color values ('04','黄色')"));
    query.exec(QObject::tr("insert into Color values ('05','绿色')"));
    query.exec(QObject::tr("insert into Color values ('06','蓝色')"));
    query.exec(QObject::tr("insert into Color values ('07','靛色')"));
    query.exec(QObject::tr("insert into Color values ('08','紫色')"));

    /**********************商品类别表*********************
     *商品类别编号、名字
    */
    query.exec(QObject::tr("CREATE TABLE G_Type(TypeId int PRIMARY KEY NOT NULL,"
                           "TypeName vchar(10))"));
    query.exec(QObject::tr("insert into G_Type values (1,'日化类')"));

    /******************************折 扣 表**********************************
     *折扣编号、折扣类型
    */
    query.exec(QObject::tr("create table Discount(DiscountId int PRIMARY KEY,"
                           "DiscountName vchar(4))"));
#endif
    return true;
}

/***************关闭数据库****************/
static bool closeConnection()
{
    QSqlDatabase::database().close();
    return 1;
}


#endif // DATABASE_H
