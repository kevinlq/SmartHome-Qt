/*智能家居控制系统数据库脚本
  作者：李棋
  时间：2015年12月8日21:14:02
  说明：本脚本创建了一下数据表：温度、湿度、烟雾浓度表
*/

drop database if exists SmartHome;
create database SmartHome;			
use SmartHome;

---设备类型表
/*
____________________
|设备编号 | 设备名 |
|         |        |
--------------------
*/
DROP TABLE IF EXISTS device_type;
CREATE TABLE device_type(
	device_id varchar(20) NOT NULL PRIMARY KEY,    		---设备编号
	device_name varchar(20) NOT NULL 					---设备名称
)ENGINE=InnoDB AUTO_INCREMENT=65 DEFAULT CHARSET=utf8;

---设备信息表
/*
________________________________________________________
|设备信息编号| 设备编号 | 设备值 | 设备日期 | 系统备注 |
|            |          |        |          |          |
--------------------------------------------------------
*/
DROP TABLE IF EXISTS device_info;
CREATE TABLE device_info (
---	device_info_id int(11) NOT NULL,	    		    ---设备信息编码
	device_id varchar(20) NOT NULL,						---设备ID
	device_value varchar(15) NOT NULL,					---设备值
	device_data varchar(30) NOT NULL,					---设备日期
	remark varchar(50) NOT NULL,						---系统备注
	PRIMARY KEY (device_data),
	FOREIGN KEY(device_id) references device_type(device_id)
) ENGINE=InnoDB AUTO_INCREMENT=65 DEFAULT CHARSET=utf8;


---设备预设值表
/*
__________________________________
设备编号  |	预设值	 |	备注     |
----------------------------------
*/
DROP TABLE IF EXISTS preinstall_value;
CREATE TABLE preinstall_value(
	device_id varchar(20) NOT NULL,						---设备ID
	device_value  varchar(10),							---预设值
	remark varchar(50),         						---备注(修改预设值的日期)
	FOREIGN KEY (device_id) references device_type(device_id)
);

INSERT INTO preinstall_value (device_id,device_value,remark)
	VALUES('01','22','');		---温度预设值为22度
INSERT INTO preinstall_value (device_id,device_value,remark)
	VALUES('02','46','');		---湿度预设值：46%
INSERT INTO preinstall_value (device_id,device_value,remark)
	VALUES('03','4','');		---烟雾浓度预设值:4%

/*创建视图---设备具体信息视图
______________________________
|设备名 | 设备值  | 设备日期 |
|       |         |          |
------------------------------
*/
CREATE VIEW v_device_info AS
	SELECT device_type.device_name,device_value,device_data
	FROM device_type,device_info
	WHERE device_type.device_id = device_info.device_id;

/*插入测试数据*/
INSERT INTO device_type values('01','温度值');
INSERT INTO device_type values('02','湿度值');
INSERT INTO device_type values('03','烟雾值');


INSERT INTO device_info(device_data,device_id,device_value,remark) 
	values('20151208102001','01','20','');
INSERT INTO device_info(device_data,device_id,device_value,remark)
	values('20151208102023','02','50','');
INSERT INTO device_info(device_data,device_id,device_value,remark)
	values('20151208102027','03','10','');

