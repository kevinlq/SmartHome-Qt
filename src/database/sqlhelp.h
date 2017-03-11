/***************************************************************
 *Copyright(c) 2014-2015 Company By LH Unigress
 *All rights reserved.
 *文件名称：数据库操作文件
 *简要描述：数据库操作文件，里边封装了常见操作sqlite和MySQL的命令集合,
 *        方便外部进行调用
 *当前版本：3.0
 *作者：Kelvin Li
 *创作日期：2014/10
 *修改日期：2015/07
 *说明：
*****************************************************************/
#ifndef SQLHELP_H
#define SQLHELP_H

#include <QObject>

class QComboBox;
class QPushButton;
class QTableView;
class QLabel;
class QSqlQueryModel;

class SqlHelp : public QObject
{
    Q_OBJECT
public:
    explicit SqlHelp(QObject *parent = 0);

    //返回某一个表中的ID最大值
    QString GetTableMaxId(const QString tableName,
                       const QString IdName);
    //返回某一个表中的某一列的值
    QString GetTableColumnValue(const QString &tableName,
                                const QString &sql);

    //查找某个ID是否存在
    bool FindIDiSEist(const QString&,const QString &,const QString &);
    //删除某个表中的某一条数据
    bool DeleteTableInfo(const QString &tableName,
                         const QString &where);

    //执行一条sql语句
    bool ExecuteSql(const QString &sql);

    //将数据绑定到下拉框中
    void BindDataToCombox(const QString &tableName,
                          const QString &tableColumnName,
                          QComboBox *cbox);

    //设置需要显示数据的表格,数据翻页对应的按钮
    void SetControlTable(QTableView *tableview,QLabel *labInfo,
                         QPushButton *btnFirst,QPushButton *btnPre,
                         QPushButton *btnNext,QPushButton *btnLast);

    //绑定数据,带行数和条件和排序
    void BindData(QString tableName,QString orderColumn,QString orderType,int rowsCount,
                  QString columnNames[], int columnWidths[]);
    void BindDataSelect(QString tableName,QString orderColumn,
                        QString orderType,QString where,int rowsCount,
                        QString columnNames[], int columnWidths[]);

    //进行数据绑定显示（不带条件的，全部显示数据表中数据）
    void BindTable(QString tableName, QTableView *tableview,
                   QString columnNames[], int columnWidths[]);
    //数据绑定并显示，带查询条件
    void BindTableWhere(QString sql, QTableView *tableview,
                   QString columnNames[], int columnWidths[]);

    //返回某个表中任意一列的数据
    QStringList getColumnData(const QString &sql);

    //查询某个表中某个字段最后一条记录
    QString getLastRecord(const QString &tableName,const QString &findValue,
                          const QString &column,const QString &columnValue);

    //返回设备表中最后一条数据
    QStringList getDeviceLastValue(const QString &device_id);
private:
    void BindData(QString sql);     //数据绑定
private slots:
    void slot_FirstPage();          //第一页
    void slot_PreviousPage();       //上一页
    void slot_NextPage();           //下一页
    void slot_LastPage();           //末一页

private:
    int StartIndex;                 //分页开始索引,每次翻页都变动
    QString TempSql;                //临时SQL语句
    QString Sql;

    int RowsCount;                  //每页显示行数
    int RowsCountAll;               //总行数
    int PageCount;                  //总页数
    int PageCurrent;                //当前第几页

    QTableView *TableView;          //显示数据的表格对象
    QLabel *LabInfo;                //显示翻页信息
    QPushButton *BtnFirst;          //第一页按钮对象
    QPushButton *BtnPre;            //上一页按钮对象
    QPushButton *BtnNext;           //下一页按钮对象
    QPushButton *BtnLast;           //末一页按钮对象

    QSqlQueryModel *QueryModel;     //查询模型
};

#endif // MYSQLHELP_H
