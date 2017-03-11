#include "sqlhelp.h"

#include <QSqlQuery>
#include <QComboBox>
#include <QPushButton>
#include <QTableView>
#include <QLabel>
#include <QSqlQueryModel>
#include <QHeaderView>
#include <QDebug>

SqlHelp::SqlHelp(QObject *parent) :
    QObject(parent)
{
    StartIndex = 0;
    TempSql = "";
    Sql = "";
    RowsCount = 0;
    RowsCountAll = 0;
    PageCount = 0;
    PageCurrent = 1;
}

/*
 *函数名：GetTableId（）
 *输入参数：数据表名，数据表中ID字段名
 *返回值：表中最大的Id值
*/
QString SqlHelp::GetTableMaxId(const QString tableName, const QString IdName)
{
    QSqlQuery query;
    QString MaxId = "";
    query.exec("SELECT MAX(" + IdName + ") FROM " + tableName + ";");
    while(query.next())
        MaxId = query.value(0).toString();
    return MaxId;
}

/*
 *函数名：GetTableColumnValue()
 *功能：返回表中某一列的值
*/
QString SqlHelp::GetTableColumnValue(const QString &tableName, const QString &sql)
{
    QSqlQuery query;
    QString value = "";
    query.exec(sql);
    while (query.next())
        value = query.value(0).toString();
    return value;
}

/*
 *功能：从某一个表中查找是否存在一个ID号为IdName的字段
 *返回：true：存在
 *     false：不存在
*/
bool SqlHelp::FindIDiSEist(const QString &tableName,
                           const QString &TableId,const QString &FindId)
{
    QString sql = "SELECT " +TableId + " FROM " + tableName;
    sql += " WHERE " + TableId +" = " + FindId;
    qDebug() <<sql;
    QSqlQuery query;
    query.exec(sql);
    if(query.next())
    {
        if (query.isValid())
            return true;
    }
    return false;
}

/*
 *函数名：
 *输入：tableName:表名
 *     where:删除的条件（主要包含所删除的ID号）
 *输出：无
*/
bool SqlHelp::DeleteTableInfo(const QString &tableName, const QString &where)
{
    QString sql = "DELETE FROM "+tableName + where;
    if (ExecuteSql(sql))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*
 *函数名：ExecuteSql()
 *输入：所要执行的sql语句
 *返回值：所执行的sql语句是否成功！
 *       成功：返回 true
 *       失败：返回 false
*/
bool SqlHelp::ExecuteSql(const QString &sql)
{
    QSqlQuery query;
    return query.exec(sql);
}

/*
 *函数：BindDataToCombox()
 *输入：数据表名，数据表中要绑定的列的名称，所要绑定的控件名称
 *返回值：无
*/
void SqlHelp::BindDataToCombox(const QString &tableName, const QString &tableColumnName,
                               QComboBox *cbox)
{
    QSqlQuery query;
    query.exec("SELECT "+tableColumnName+" FROM "+tableName+" ORDER BY "+tableColumnName+" DESC");
    while(query.next())
    {
        cbox->addItem(query.value(0).toString());
    }
}

/*
 *说明：设置显示数据的表格控件,当前翻页信息的标签控件等
 *输入参数：tableview:要显示的tableview名称
 *         labinfo:显示的信息
 *         btnFirst:第一页按钮
 *         btnPre:前一页按钮
 *         btnNext:下一页按钮
 *         btnLast:最后一页按钮
 *输出参数：无
*/
void SqlHelp::SetControlTable(QTableView *tableview, QLabel *labInfo, QPushButton *btnFirst,
                              QPushButton *btnPre, QPushButton *btnNext, QPushButton *btnLast)
{
    TableView = tableview;
    LabInfo = labInfo;
    BtnFirst = btnFirst;
    BtnPre = btnPre;
    BtnNext = btnNext;
    BtnLast = btnLast;
    QueryModel = new QSqlQueryModel(TableView);

    connect(BtnFirst,SIGNAL(clicked()),this,SLOT(slot_FirstPage()));
    connect(BtnPre,SIGNAL(clicked()),this,SLOT(slot_PreviousPage()));
    connect(BtnNext,SIGNAL(clicked()),this,SLOT(slot_NextPage()));
    connect(BtnLast,SIGNAL(clicked()),this,SLOT(slot_LastPage()));
}

/*
 *说明：分页绑定数据到表格、排序方式
*/
void SqlHelp::BindData(QString tableName, QString orderColumn, QString orderType,
                       int rowsCount, QString columnNames[], int columnWidths[])
{
    StartIndex = 0;//重置开始索引
    PageCurrent = 1;
    RowsCount = rowsCount;

    //开始分页绑定数据前,计算好总数据量以及行数
    TempSql = "select count(*) from "+tableName;
    QSqlQuery query;
    query.prepare(TempSql);
    query.exec();
    query.first();
    RowsCountAll = query.value(0).toInt();

    int yushu = RowsCountAll % RowsCount;
    //不存在余数,说明是整行,例如300%5==0
    if (yushu == 0)
    {
        if (RowsCountAll > 0 && RowsCountAll < RowsCount)
        {
            PageCount = 1;
        }
        else
        {
            PageCount=RowsCountAll/RowsCount;
        }
    }
    else
    {
        PageCount=RowsCountAll/RowsCount+1;
    }

    TempSql = "select * from "+tableName+" where 1=1 order by "+orderColumn+" "+orderType;
    Sql = QString("%1 limit %2,%3;").arg(TempSql).arg(StartIndex).arg(RowsCount);//组织分页SQL语句
    BindData(Sql);

    //依次设置列标题、列宽等
    for (int i = 0;i<TableView->model()->columnCount();i++)
    {
        QueryModel->setHeaderData(i,Qt::Horizontal,columnNames[i]);//设置列标题
        TableView->setColumnWidth(i,columnWidths[i]);//设置列宽
    }

    TableView->horizontalHeader()->setHighlightSections(false);             //点击表头时不对表头光亮
    TableView->setSelectionMode(QAbstractItemView::SingleSelection);    //选中模式为单行选中
    TableView->setSelectionBehavior(QAbstractItemView::SelectRows);         //选中整行
    TableView->setStyleSheet( "QTableView::item:hover{background-color:rgb(117,187,226,70)}"
                              "QTableView::item:selected{background-color:#0997C0}");
}

//分页绑定查询数据到表格、排序方式
void SqlHelp::BindDataSelect(QString tableName, QString orderColumn, QString orderType,
                             QString where, int rowsCount, QString columnNames[], int columnWidths[])
{
    StartIndex = 0;//重置开始索引
    PageCurrent = 1;
    RowsCount = rowsCount;

    //开始分页绑定数据前,计算好总数据量以及行数
    TempSql = "select count(*) from "+tableName+" "+where;
    QSqlQuery query;
    query.prepare(TempSql);//分行写的时候注意空格不能少
    query.exec();
    query.first();
    RowsCountAll = query.value(0).toInt();

    int yushu = RowsCountAll % RowsCount;
    //不存在余数,说明是整行,例如300%5==0
    if (yushu == 0)
    {
        if (RowsCountAll > 0 && RowsCountAll < RowsCount)
        {
            PageCount = 1;
        }
        else
        {
            PageCount = RowsCountAll/RowsCount;
        }
    }
    else
    {
        PageCount = RowsCountAll/RowsCount+1;
    }

    TempSql = "select * from "+tableName+" "+where+" order by "+orderColumn+" "+orderType;
    Sql = QString("%1 limit %2,%3;").arg(TempSql).arg(StartIndex).arg(RowsCount);//组织分页SQL语句
    BindData(Sql);

    //依次设置列标题、列宽等
    for (int i = 0;i < TableView->model()->columnCount();i++)
    {
        QueryModel->setHeaderData(i,Qt::Horizontal,columnNames[i]);//设置列标题
        TableView->setColumnWidth(i,columnWidths[i]);//设置列宽
    }


    TableView->horizontalHeader()->setHighlightSections(false);//点击表头时不对表头光亮
    TableView->setSelectionMode(QAbstractItemView::SingleSelection);//选中模式单行选中
    TableView->setSelectionBehavior(QAbstractItemView::SelectRows);//选中整行
    TableView->setStyleSheet( "QTableView::item:hover{background-color:rgb(98,188,214,60)}"
                              "QTableView::item:selected{background-color:#0997C0}");
}

/*
 *函数名：BindTable（）
 *输入参数：
 *输出参数：无
*/
void SqlHelp::BindTable(QString tableName, QTableView *tableview,
                        QString columnNames[], int columnWidths[])
{
    TableView = tableview;
    QSqlQueryModel *model = new QSqlQueryModel(this);
    QString sql = "SELECT *FROM " + tableName;
    model->setQuery(sql);
    TableView->setModel(model);

    //依次设置列标题、列宽等
    for (int i = 0;i < TableView->model()->columnCount();i++)
    {
        model->setHeaderData(i,Qt::Horizontal,columnNames[i]);//设置列标题
        TableView->setColumnWidth(i,columnWidths[i]);//设置列宽
    }


    TableView->horizontalHeader()->setHighlightSections(false);//点击表头时不对表头光亮
    TableView->setSelectionMode(QAbstractItemView::SingleSelection);//选中模式单行选中
    TableView->setSelectionBehavior(QAbstractItemView::SelectRows);//选中整行
    TableView->setStyleSheet( "QTableView::item:hover{background-color:rgb(98,188,214,60)}"
                              "QTableView::item:selected{background-color:#0997C0}");
}

/*
 *功能：带查询条件的数据绑定显示
*/
void SqlHelp::BindTableWhere(QString sql,QTableView *tableview,
                             QString columnNames[], int columnWidths[])
{
    TableView = tableview;
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery(sql);
    TableView->setModel(model);

    //依次设置列标题、列宽等
    for (int i = 0;i < TableView->model()->columnCount();i++)
    {
        model->setHeaderData(i,Qt::Horizontal,columnNames[i]);//设置列标题
        TableView->setColumnWidth(i,columnWidths[i]);//设置列宽
    }


    TableView->horizontalHeader()->setHighlightSections(false);//点击表头时不对表头光亮
    TableView->setSelectionMode(QAbstractItemView::SingleSelection);//选中模式单行选中
    TableView->setSelectionBehavior(QAbstractItemView::SelectRows);//选中整行
    TableView->setStyleSheet( "QTableView::item:hover{background-color:rgb(98,188,214,60)}"
                              "QTableView::item:selected{background-color:#0997C0}");
}

QStringList SqlHelp::getColumnData(const QString &sql)
{
    QStringList data_list;
    QSqlQuery query;
    query.exec(sql);
    while (query.next())
    {
        data_list.append(query.value(0).toString());
    }
    return data_list;
}

/*
 *说明：查询表中最后一条记录
*/
QString SqlHelp::getLastRecord(const QString &tableName, const QString &findValue,
                               const QString &column,const QString &columnValue)
{
    QString sql = "SELECT "+findValue +" FROM "+tableName;
    sql += " WHERE "+column +" = '" +columnValue+"' ";
    sql += "ORDER BY device_data DESC";
    QSqlQuery query;
    query.exec(sql);
    query.next();

    return query.value(0).toString();
}

QStringList SqlHelp::getDeviceLastValue(const QString &device_id)
{
    QStringList value_list;
    QString sql = "SELECT [device_value],[device_data] FROM [device_info]";
    sql += " WHERE [device_id] = '"+device_id +"' ORDER BY device_data DESC LIMIT 1";
    QSqlQuery query;
    query.exec(sql);
    query.next();
    value_list <<query.value(0).toString() <<query.value(1).toString();
    return value_list;
}

/*
 *说明：绑定一条SQL语句
 *本文件调用(SetControlTable()函数调用)
*/
void SqlHelp::BindData(QString sql)
{
    QueryModel->setQuery(sql);
    TableView->setModel(QueryModel);
    LabInfo->setText(QString("共有%1条数据  共%2页  当前第%3页").arg(RowsCountAll).arg(PageCount).arg(PageCurrent));
}

//第一页
void SqlHelp::slot_FirstPage()
{
    if (PageCount > 1)
    {
        StartIndex = 0;
        PageCurrent = 1;
        Sql = QString("%1 limit %2,%3;").arg(TempSql).arg(StartIndex).arg(RowsCount);//组织分页SQL语句
        BindData(Sql);
    }
}

//上一页
void SqlHelp::slot_PreviousPage()
{
    if (PageCurrent > 1)
    {
        PageCurrent--;
        StartIndex-=RowsCount;
        Sql = QString("%1 limit %2,%3;").arg(TempSql).arg(StartIndex).arg(RowsCount);//组织分页SQL语句
        BindData(Sql);
    }
}

//下一页
void SqlHelp::slot_NextPage()
{
    if (PageCurrent < PageCount)
    {
        PageCurrent++;
        StartIndex+=RowsCount;
        Sql = QString("%1 limit %2,%3;").arg(TempSql).arg(StartIndex).arg(RowsCount);//组织分页SQL语句
        BindData(Sql);
    }
}

//末一页
void SqlHelp::slot_LastPage()
{
    if (PageCount > 0)
    {
        StartIndex = (PageCount - 1)*RowsCount;
        PageCurrent = PageCount;
        Sql = QString("%1 limit %2,%3;").arg(TempSql).arg(StartIndex).arg(RowsCount);//组织分页SQL语句
        BindData(Sql);
    }
}
