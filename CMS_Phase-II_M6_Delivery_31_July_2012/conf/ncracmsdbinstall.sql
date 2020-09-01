-- MySQL Administrator dump 1.4
--
-- ------------------------------------------------------
-- Server version	5.2.3-falcon-alpha-community-nt


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


--
-- Create schema ncracmsdb
--

CREATE DATABASE IF NOT EXISTS ncracmsdb;
USE ncracmsdb;

--
-- Definition of table `t_alarm`
--

DROP TABLE IF EXISTS `ncracmsdb`.`t_alarm`;
CREATE TABLE  `ncracmsdb`.`t_alarm` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT '(PK) auto generated',
  `name` varchar(45) DEFAULT NULL, INDEX USING BTREE (name),
  `alarm_id` varchar(15) NOT NULL,  INDEX USING BTREE (alarm_id),
  `level` varchar(10) NOT NULL COMMENT 'level is of alarm (L1/L2/L3)',
  `subsystem_name` varchar(20) DEFAULT NULL  COMMENT 'Subsystem name',
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'Timestamp when the alarm was received',
  `xmldata` varchar(1000) DEFAULT NULL COMMENT 'Xml data sent or received from subsystem',
  `message` varchar(200) DEFAULT NULL COMMENT 'Message associated with this Alarm',
  `ack_username` varchar(30) DEFAULT NULL,
  `is_ack` tinyint(1) DEFAULT '0',
  `is_clear` tinyint(1) unsigned zerofill NOT NULL DEFAULT '0',
  `clear_username` varchar(30) DEFAULT NULL,
  `lastUpdatedTimeStamp` timestamp NULL DEFAULT NULL COMMENT 'Latest Timestamp when the alarm was received',
  `description` varchar(250) DEFAULT NULL COMMENT 'Description of alarm',
  `status` tinyint(1) unsigned zerofill NOT NULL DEFAULT '1' COMMENT 'enable/disable alarm',
  `status_username` varchar(30) DEFAULT NULL  COMMENT 'name of user who enabled/disabled alarm',
  PRIMARY KEY (`id`),
  KEY `subsystem_name` (`subsystem_name`),
  CONSTRAINT `t_alarm_ibfk_1` FOREIGN KEY (`subsystem_name`) REFERENCES `t_subsystem` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


/*!40000 ALTER TABLE `t_alarm` DISABLE KEYS */;
/*!40000 ALTER TABLE `t_alarm` ENABLE KEYS */;


--
-- Definition of table `t_catalog`
--

DROP TABLE IF EXISTS `ncracmsdb`.`t_catalog`;
CREATE TABLE `t_catalog` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT '(PK) Auto generated ID ',
  `source` varchar(50) NOT NULL COMMENT '(UNIQUE) object source name',
  `ra` varchar(30) DEFAULT NULL COMMENT 'RA of object',
  `declination` varchar(30) DEFAULT NULL COMMENT 'DEC of object',
  `epoch` varchar(30) DEFAULT NULL COMMENT 'EPOCH of object',
  `band` varchar(30) DEFAULT NULL,
  `fluxdensity` varchar(30) DEFAULT NULL,
  `source_velocity` varchar(30) DEFAULT NULL,
  `morph_code` varchar(20) DEFAULT NULL,
  `SI_ESI` varchar(30) DEFAULT NULL,
  `source_vel_ref_frame` varchar(20) DEFAULT NULL,
  `source_vel_type` varchar(30) DEFAULT NULL,
  `comment` varchar(256) DEFAULT NULL,
  `alias` varchar(30) DEFAULT NULL,
  `username` varchar(45) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `unique_object` (`source`,`ra`,`declination`,`epoch`,`username`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;



--
-- Definition of table `t_commandlog`
--


DROP TABLE IF EXISTS `ncracmsdb`.`t_commandlog`;
CREATE TABLE  `ncracmsdb`.`t_commandlog` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT '(PK) Auto generated ID ',
  `type` varchar(20) NOT NULL COMMENT 'Subsystem REQUEST/RESPONSE/EVENT',
  `subsystem_name` varchar(20) NOT NULL COMMENT '(FK) subsystem for which this event occurred',
  `user_name` varchar(20) NOT NULL COMMENT 'user who sent the command', INDEX USING BTREE (user_name),
  `command_id` varchar(20) DEFAULT NULL COMMENT 'Unique id is of command',
  `sequence_number` int(10) unsigned NOT NULL COMMENT 'Sequence number of command',
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'timestamp is of command when sent or when received',INDEX USING BTREE (timestamp),
  `response_type` varchar(10) DEFAULT NULL COMMENT 'response_type (SUCCESS/FAIL/EVENT)',
  `xmldata` varchar(5000) DEFAULT NULL COMMENT 'Xml data sent or 	received from subsystem',
  `message` varchar(50) DEFAULT NULL COMMENT 'Message associated with this command',
  `command_name` varchar(45) NOT NULL COMMENT 'command name',
  `event` varchar(10) DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `subsystem_name` (`subsystem_name`),
  CONSTRAINT `t_commandlog_ibfk_1` FOREIGN KEY (`subsystem_name`) REFERENCES `t_subsystem` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;
--
-- Dumping data for table `t_commandlog`
--

/*!40000 ALTER TABLE `t_commandlog` DISABLE KEYS */;
/*!40000 ALTER TABLE `t_commandlog` ENABLE KEYS */;


--
-- Definition of table `t_group_permission`
--

DROP TABLE IF EXISTS `ncracmsdb`.`t_group_permission`;
CREATE TABLE `ncracmsdb`.`t_group_permission` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `grouppermcode` varchar(100) NOT NULL,
  `value` varchar(100) DEFAULT NULL,
  `isCustomizable` varchar(45) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `t_group_permission`
--

/*!40000 ALTER TABLE `ncracmsdb`.`t_group_permission` DISABLE KEYS */;
INSERT INTO `ncracmsdb`.`t_group_permission` (`id`,`grouppermcode`,`value`,`isCustomizable`) VALUES
 (1,'BF_GENERAL','DEFAULT PERMISSIONS','NO'),
 (2,'BF_VIEW_USERMGMT','USER MANAGEMENT','YES'),
 (3,'BF_VIEW_EXPERTTAB','EXPERT TAB','YES'),
 (4,'BF_VIEW_TUNERECEIVER','TUNE RECEIVER','YES'),
 (5,'BF_VIEW_DISPLAY','CATALOG AND SETTINGS TAB','YES'),
 (6,'BF_VIEW_MANUALMODE','MANUAL MODE','YES'),
 (7,'BF_VIEW_FORCELOGOUT','FORCE LOGOUT','YES'),
 (8,'BF_VIEW_BATCHMODE','BATCH MODE','YES'),
 (9,'BF_VIEW_CMDLOG','COMMAND LOG','YES'),
 (10,'BF_VIEW_ROLEMGMT','ROLE MANAGEMENT','YES'),
 (11,'BF_VIEW_DISPLAY_SAVE_SYSTEMCATALOG','SYSTEM CATALOG AND SETTINGS TAB','YES'),
 (12,'BF_VIEW_ENGINEERING_servo','SERVO_ENGINEERING','YES'),
 (13,'BF_VIEW_DASHBOARD','CMS DASHBOARD','YES'),
 (14,'BF_OPS_MAINTAINANCE','MAINTENANCE STATE','YES'),
 (15,'BF_ENABLE_DISABLE_ALARM','ENABLE DISABLE ALARM','YES'),
 (16,'BF_CLEAR_ALARM','CLEAR ALARM','YES'),
 (17,'BF_CHANGE_STATE','CHANGE CMS STATE','YES'),
 (18,'BF_ACKNOWLEDGE_RECENTALARM','ACKNOWLEDGE RECENT ALARM','YES'),
 (19,'BF_OP_SINGLE_USAGE_MODE','BF_OP_SINGLE_USAGE_MODE','YES'),
 (20,'BF_VIEW_METADATA','META DATA','YES'),
 (21,'BF_SHOW_CMSSETTING','CHANGE CMS SETTINGS','YES');
 
/*!40000 ALTER TABLE `t_group_permission` ENABLE KEYS */;


--
-- Definition of table `t_permission`
--

DROP TABLE IF EXISTS `ncracmsdb`.`t_permission`;
CREATE TABLE `ncracmsdb`.`t_permission` (
  `id` int(10) unsigned zerofill NOT NULL AUTO_INCREMENT,
  `permcode` varchar(100) NOT NULL,
  `description` varchar(100) DEFAULT NULL,
  `parent_id` int(10) unsigned zerofill NOT NULL,
  PRIMARY KEY (`id`),
  KEY `parent_id` (`parent_id`),
  CONSTRAINT `t_permission_ibfk_1` FOREIGN KEY (`parent_id`) REFERENCES `t_group_permission` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `t_permission`
--

/*!40000 ALTER TABLE `ncracmsdb`.`t_permission` DISABLE KEYS */;
INSERT INTO `ncracmsdb`.`t_permission` (`id`,`permcode`,`description`,`parent_id`) VALUES
 (0000000001,'BF_ADD_USER','addNewUser.htm',0000000002),
 (0000000002,'BF_EDIT_USER','editUser.htm',0000000002),
 (0000000003,'BF_SHOW_HOME','showHome.htm',0000000001),
 (0000000005,'BF_CONTROL_STATUS','controlStatus/*.htm',0000000001),
 (0000000006,'BF_SHOW_ALARMS','showAllAlarms.htm',0000000001),
 (0000000007,'BF_ACK_ALARM','showAllAlarms.htm',0000000001),
 (0000000008,'BF_GET_CMDLOG','getCommandLog.htm',0000000001),
 (0000000009,'BF_CHANGE_PWD','changePassword.htm',0000000001),
 (0000000010,'BF_PLOT','plot.htm',0000000001),
 (0000000011,'BF_CATALOG','catalogXml.htm',0000000001),
 (0000000012,'BF_POLAR_XML','polarXml.htm',0000000001),
 (0000000013,'BF_SHOW_CMSINFO','showCmsInfo.htm',0000000001),
 (0000000014,'BF_CREATE_EXCEL','createExcel.htm',0000000001),
 (0000000015,'BF_CHANGE_HEADER','headerChange.htm',0000000001),
 (0000000016,'BF_USER_MESSAGE','userMessage.htm',0000000001),
 (0000000017,'BF_OPEN_MSGCONSOLE','openMessageConsole.htm',0000000001),
 (0000000018,'BF_SHOW_CMSSETTING','showCmsSetting.htm',0000000021),
 (0000000019,'BF_ABOUTUS','aboutUs.htm',0000000001),
 (0000000020,'BF_SHOW_TRACKINGSTATUS','showTrackingStatus.htm',0000000001),
 (0000000021,'BF_TRACKINGSTATUS','trackingStatus.htm',0000000001),
 (0000000022,'BF_RECEIVERSTATUS','receiverStatus.htm',0000000001),
 (0000000023,'BF_SHOW_RECEIVERSTATUS','showReceiverStatus.htm',0000000001),
 (0000000024,'BF_SHOWALL_USERS','showAllUsers.htm',0000000002),
 (0000000025,'BF_DELETE_USER','deleteUser.htm',0000000002),
 (0000000026,'BF_SHOWOL_USERS','showAllOlUsers.htm',0000000007),
 (0000000027,'BF_FORCE_LGOUT','forceLogoutUser.htm',0000000007),
 (0000000028,'BF_FETCH_CMDSTATUS','fetchCommandExecutionStatus.htm',0000000003),
 (0000000029,'BF_EXECUTE_CMD','executeCommand.htm',0000000003),
 (0000000030,'BF_RECEIVERTEMPLATE_OPS','receiverTeplate/*.htm',0000000004),
 (0000000031,'BF_RECEIVER_CMD_OPS','receiverCommand/*.htm',0000000004),
 (0000000032,'BF_UPLOAD_CATALOG','uploadCatalog.htm',0000000005),
 (0000000033,'BF_PLOT_FORMAT','plotFormatter.htm',0000000005),
 (0000000034,'BF_MANUALMODE_CMD','manualmodecommand/*.htm',0000000006),
 (0000000035,'BF_LOAD_MANUALMODE','loadmanualmode.htm',0000000006),
 (0000000036,'BF_SAVE_MANUALMODE','manualmodeloadsave/*.htm',0000000006),
 (0000000037,'BF_SAVE_SYSTEMCATALOG','sytem upload catalog',0000000011),
 (0000000038,'BF_SHOW_ROLE','showRoles.htm',0000000010),
 (0000000039,'BF_EDIT_ROLE','editRole.htm',0000000010),
 (0000000040,'BF_DELETE_ROLE','deleteRole.htm',0000000010),
 (0000000042,'BF_LOGIN_MAINTAINANCE','login.htm',0000000014),
 (0000000043,'BF_ALARM_STATUS','recentAlarmStatusController.htm',0000000015),
 (0000000044,'BF_CLEAR_ALARM_STATUS','aknowledgeRecentAlarm.htm',0000000016),
 (0000000045,'BF_VIEW_DASHBOARD','showDashboard.htm',0000000001),
 (0000000046,'BF_ACKNOWLEDGE_RECENTALARM','aknowledgeRecentAlarm.htm',0000000018),
 (0000000047,'BF_META_DATA','spectralPulsarCustomTemplate/*.htm',0000000020);
/*!40000 ALTER TABLE `ncracmsdb`.`t_permission` ENABLE KEYS */;


--
-- Definition of table `t_role`
--

DROP TABLE IF EXISTS `ncracmsdb`.`t_role`;
CREATE TABLE `ncracmsdb`.`t_role` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT '(PK) Auto generated ID ',
  `role_name` varchar(20) NOT NULL COMMENT '(UNIQUE) Role name (ADMIN/EXPERT/OBSERVER )',
  `description` varchar(20) DEFAULT NULL COMMENT 'Description of Role',
  PRIMARY KEY (`id`),
  UNIQUE KEY `role_name` (`role_name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `t_role`
--

/*!40000 ALTER TABLE `ncracmsdb`.`t_role` DISABLE KEYS */;
INSERT INTO `ncracmsdb`.`t_role` (`id`,`role_name`,`description`) VALUES
 (1,'ROLE_ADMIN','Admin'),
 (2,'ROLE_EXPERT','Expert'),
 (3,'ROLE_ASTRONOMER','Astronomer'),
 (4,'ROLE_CO-ASTRONOMER','Co-Astronomer'),
 (5,'ROLE_OBSERVER','Observer'),
 (6,'ROLE_PREOBSERVATION','Pre Observation Role'),
 (7,'ROLE_ENGINEER','Engineer');
/*!40000 ALTER TABLE `t_role` ENABLE KEYS */;


--
-- Definition of table `t_role_permission`
--

DROP TABLE IF EXISTS `ncracmsdb`.`t_role_permission`;
CREATE TABLE `ncracmsdb`.`t_role_permission` (
  `role_id` int(10) unsigned NOT NULL,
  `parent_id` int(10) unsigned NOT NULL,
  PRIMARY KEY (`role_id`,`parent_id`),
  KEY `fk_permission_parent` (`parent_id`),
  CONSTRAINT `fk_permission_parent` FOREIGN KEY (`parent_id`) REFERENCES `t_group_permission` (`id`),
  CONSTRAINT `fk_roles` FOREIGN KEY (`role_id`) REFERENCES `t_role` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `t_role_permission`
--

/*!40000 ALTER TABLE `ncracmsdb`.`t_role_permission` DISABLE KEYS */;
INSERT INTO `ncracmsdb`.`t_role_permission` (`role_id`,`parent_id`) VALUES
 (1,1),
 (2,1),
 (3,1),
 (4,1),
 (5,1),
 (1,2),
 (1,3),
 (2,3),
 (3,3),
 (1,4),
 (2,4),
 (3,4),
 (1,5),
 (2,5),
 (3,5),
 (1,6),
 (2,6),
 (3,6),
 (1,7),
 (1,8),
 (2,8),
 (3,8),
 (1,9),
 (2,9),
 (1,10),
 (1,11),
 (2,11),
 (2,12),
 (2,13),
 (6,1),
 (6,5),
 (6,8),
 (1,14),
 (2,14),
 (7,1),
 (7,14),
 (2,15),
 (2,16),
 (1,19),
 (2,19),
 (1,20),
 (2,20), 
 (1,21),
 (2,21);
/*!40000 ALTER TABLE `ncracmsdb`.`t_role_permission` ENABLE KEYS */;


--
-- Definition of table `t_schedule`
--

DROP TABLE IF EXISTS `ncracmsdb`.`t_schedule`;
CREATE TABLE `ncracmsdb`.`t_schedule` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT '(PK) auto generated id',
  `proposal_code` varchar(20) NOT NULL COMMENT '(UNIQUE)  Proposal Code',
  `description` varchar(50) DEFAULT NULL COMMENT 'Description of  proposal',
  `start_time` timestamp NULL DEFAULT NULL COMMENT 'Start time of Schedule ',
  `end_time` timestamp NULL DEFAULT NULL COMMENT 'End time of Schedule',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `t_schedule`
--

/*!40000 ALTER TABLE `ncracmsdb`.`t_schedule` DISABLE KEYS */;
/*!40000 ALTER TABLE `ncracmsdb`.`t_schedule` ENABLE KEYS */;


--
-- Definition of table `t_subsystem`
--

DROP TABLE IF EXISTS `ncracmsdb`.`t_subsystem`;
CREATE TABLE `ncracmsdb`.`t_subsystem` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT '(PK) Auto generated ID ',
  `name` varchar(20) NOT NULL COMMENT '(UNIQUE) subsystem name',
  PRIMARY KEY (`id`),
  UNIQUE KEY `name` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `t_subsystem`
--

/*!40000 ALTER TABLE `ncracmsdb`.`t_subsystem` DISABLE KEYS */;
INSERT INTO `t_subsystem` (`id`,`name`) VALUES 
 (1,'backend'),
 (4,'frontend'),
 (5,'sentinal'),
 (2,'servo'),
 (3,'sigcon');
/*!40000 ALTER TABLE `ncracmsdb`.`t_subsystem` ENABLE KEYS */;


--
-- Definition of table `t_user`
--

DROP TABLE IF EXISTS `ncracmsdb`.`t_user`;
CREATE TABLE `ncracmsdb`.`t_user` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT '(PK) autogenerated id',
  `username` varchar(20) NOT NULL COMMENT '(UNIQUE)  username - Required',
  `passwd` varchar(200) NOT NULL,
  `state` varchar(10) DEFAULT NULL COMMENT 'state of User (ACTIVE/DISABLED) - Required',
  `name` varchar(30) NOT NULL COMMENT 'name of User',
  `email` varchar(100)NOT NULL COMMENT 'email id of User - Required',
  `contact_number` varchar(15) NOT NULL COMMENT 'contact number of User',
  `address` varchar(200) DEFAULT NULL COMMENT 'address of User',
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `t_user`
--

/*!40000 ALTER TABLE `ncracmsdb`.`t_user` DISABLE KEYS */;
INSERT INTO `t_user` (`id`,`username`,`passwd`,`state`,`name`,`email`,`contact_number`,`address`) VALUES 
 (1,'admin','21232f297a57a5a743894a0e4a801fc3','ACTIVE','admin','admin@gmail.com','9970777070',NULL);
/*!40000 ALTER TABLE `ncracmsdb`.`t_user` ENABLE KEYS */;


--
-- Definition of table `t_user_role`
--

DROP TABLE IF EXISTS `ncracmsdb`.`t_user_role`;
CREATE TABLE `ncracmsdb`.`t_user_role` (
  `user_id` int(10) unsigned NOT NULL COMMENT '(FK) id of user',
  `role_id` int(10) unsigned NOT NULL COMMENT '(FK) id of security_role',
  KEY `user_id` (`user_id`),
  KEY `role_id` (`role_id`),
  CONSTRAINT `t_user_role_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `t_user` (`id`),
  CONSTRAINT `t_user_role_ibfk_2` FOREIGN KEY (`role_id`) REFERENCES `t_role` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `t_user_role`
--

/*!40000 ALTER TABLE `t_user_role` DISABLE KEYS */;
INSERT INTO `t_user_role` (`user_id`,`role_id`) VALUES 
 (1,1);
/*!40000 ALTER TABLE `t_user_role` ENABLE KEYS */;


--
-- Definition of table `t_user_schedule`
--

DROP TABLE IF EXISTS `ncracmsdb`.`t_user_schedule`;
CREATE TABLE `ncracmsdb`.`t_user_schedule` (
  `user_id` int(10) unsigned NOT NULL COMMENT '(FK)  username of user',
  `schedule_id` int(10) unsigned NOT NULL COMMENT '(FK)  Proposal Code',
  KEY `foreignkey1` (`user_id`),
  KEY `schedule_id` (`schedule_id`),
  CONSTRAINT `t_user_schedule_ibfk_1` FOREIGN KEY (`user_id`) REFERENCES `t_user` (`id`),
  CONSTRAINT `t_user_schedule_ibfk_2` FOREIGN KEY (`schedule_id`) REFERENCES `t_schedule` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;


DROP TABLE IF EXISTS `ncracmsdb`.`t_monitoring_information`;
CREATE TABLE `ncracmsdb`.`t_monitoring_information` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `subsystem_name` varchar(45) NOT NULL, INDEX USING BTREE (subsystem_name),
  `parameter_name` varchar(45) NOT NULL, INDEX USING BTREE (parameter_name),
  `parameter_value` varchar(1000) NOT NULL,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  KEY `fk_1` (`subsystem_name`),
  CONSTRAINT `fk_1` FOREIGN KEY (`subsystem_name`) REFERENCES `t_subsystem` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;



--
-- Dumping data for table `t_user_schedule`
--

/*!40000 ALTER TABLE `t_user_schedule` DISABLE KEYS */;
/*!40000 ALTER TABLE `t_user_schedule` ENABLE KEYS */;


--
-- Definition of table `t_recent_alarm`
--

DROP TABLE IF EXISTS `ncracmsdb`.`t_recent_alarm`;
CREATE TABLE  `ncracmsdb`.`t_recent_alarm` (
  `alarm_id` varchar(15) NOT NULL, INDEX USING BTREE (alarm_id),
  `name` varchar(80) NOT NULL DEFAULT '', INDEX USING BTREE (name),
  `level` varchar(10) NOT NULL COMMENT 'level is of alarm (L1/L2/L3)',
  `subsystem_name` varchar(20) NOT NULL DEFAULT '' COMMENT 'Subsystem name', INDEX USING BTREE (subsystem_name),
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT 'Timestamp when the alarm was received',
  `xmldata` varchar(1000) DEFAULT NULL COMMENT 'Xml data sent or received from subsystem',
  `message` varchar(200) DEFAULT NULL COMMENT 'Message associated with this Alarm',
  `ack_username` varchar(30) DEFAULT NULL,
  `is_ack` tinyint(1) unsigned zerofill NOT NULL,
  `is_clear` tinyint(1) unsigned zerofill NOT NULL DEFAULT '0',
  `clear_username` varchar(30) DEFAULT NULL,
  `lastUpdatedTimeStamp` timestamp NULL DEFAULT NULL COMMENT 'Latest Timestamp when the alarm was received',
  `description` varchar(250) DEFAULT NULL COMMENT 'Description of alarm',
  `status` tinyint(1) unsigned zerofill NOT NULL DEFAULT '1' COMMENT 'enable/disable alarm',
  `status_username` varchar(30) DEFAULT NULL  COMMENT 'name of user who enabled/disabled alarm',
  PRIMARY KEY (`subsystem_name`,`name`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Definition of table `t_state`
--

DROP TABLE IF EXISTS `ncracmsdb`.`t_state`;
CREATE TABLE `t_state` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `currentstate` varchar(30) NOT NULL COMMENT 'current state', INDEX USING BTREE (currentstate),
  `previousstate` varchar(30) NOT NULL COMMENT 'new state',
  `transitiontime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'transition Time',
  `transitionreason` varchar(200) NOT NULL COMMENT 'transition Reason',  
  `username` varchar(45) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

DROP TABLE IF EXISTS `ncracmsdb`.`t_recent_monitoring_data`;
CREATE TABLE  `ncracmsdb`.`t_recent_monitoring_data` (
  `subsystem_name` varchar(45) NOT NULL,INDEX USING BTREE (subsystem_name),
  `parameter_name` varchar(45) NOT NULL,
  `parameter_value` varchar(1000) NOT NULL,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`subsystem_name`,`parameter_name`) USING BTREE,
  KEY `fk_1` (`subsystem_name`),
  CONSTRAINT `FK_t_subsystem_name` FOREIGN KEY (`subsystem_name`) REFERENCES `t_subsystem` (`name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `t_recent_monitoring_data`
--

/*!40000 ALTER TABLE `t_recent_monitoring_data` DISABLE KEYS */;
/*!40000 ALTER TABLE `t_recent_monitoring_data` ENABLE KEYS */;


/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;


DROP TABLE IF EXISTS `ncracmsdb`.`t_user_alarm_ops`;
CREATE TABLE  `ncracmsdb`.`t_user_alarm_ops` (
  `username` varchar(20) NOT NULL,
  `mute_critical` tinyint(1) unsigned zerofill NOT NULL DEFAULT '0',
  `mute_non_critical` tinyint(1) unsigned zerofill NOT NULL DEFAULT '0',
  PRIMARY KEY (`username`) USING BTREE,
  CONSTRAINT `t_user_alarm_ops_ibfk_1` FOREIGN KEY (`username`) REFERENCES `t_user` (`username`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

source p_saveAlarmInfo.sql;
source p_saveMonitoringData.sql;