DELIMITER $$

DROP PROCEDURE IF EXISTS `ncracmsdb`.`p_saveAlarmInfo` $$
CREATE PROCEDURE `ncracmsdb`.`p_saveAlarmInfo` (IN subsystemName varchar(20), IN alarmName varchar(80), IN alarm_id varchar(15), IN level varchar(10),
IN xmldata varchar(1000), IN message varchar(200), IN is_ack tinyint(1), IN ack_username varchar(30),
IN is_clear tinyint(1), IN clear_username varchar(30), IN lastupdatedTime Timestamp,
IN description varchar(250), IN status tinyint(1), IN status_username varchar(30))
BEGIN

DECLARE currentTime Timestamp default CURRENT_TIMESTAMP();
DECLARE paramCount INT DEFAULT 0;

select count(1) into paramCount from t_recent_alarm
where subsystem_name = subsystemName and name = alarmName;

if(paramCount > 0) then
  update t_recent_alarm
    set
      level = level,
      timestamp = currentTime,
      xmldata = xmldata,
      message = message,
      ack_username =ack_username,
      is_ack = is_ack,
      is_clear = is_clear,
      clear_username = clear_username,
      lastUpdatedTimeStamp = lastupdatedTime ,
      description = description,
      status = status,
      status_username =status_username
    where subsystem_name = subsystemName
    and name = alarmName;
else
  insert into t_recent_alarm (alarm_id ,name , level ,subsystem_name , timestamp, xmldata , message , ack_username ,is_ack ,
                              is_clear , clear_username , lastUpdatedTimeStamp ,description, status , status_username)
  values (alarm_id ,alarmName , level ,subsystemName ,currentTime,  xmldata , message , ack_username ,is_ack , is_clear , clear_username ,
  lastupdatedTime ,description, status , status_username);

end if;
  insert into t_alarm (name,alarm_id , level ,subsystem_name , timestamp, xmldata , message , ack_username ,is_ack ,
                              is_clear , clear_username , lastUpdatedTimeStamp ,description, status , status_username)
  values (alarmName ,alarm_id , level ,subsystemName ,currentTime,  xmldata , message , ack_username ,is_ack , is_clear , clear_username ,
  lastupdatedTime ,description, status , status_username);


END $$

DELIMITER ;