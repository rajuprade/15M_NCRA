DELIMITER $$

DROP PROCEDURE IF EXISTS `ncracmsdb`.`p_storeMonitoringInfo` $$
CREATE PROCEDURE `ncracmsdb`.`p_storeMonitoringInfo` (IN subsystemName varchar(255) , IN paramName varchar(255) ,
  IN paramValue varchar(255) , IN storeInHistory int )
BEGIN


DECLARE currentTime Timestamp default CURRENT_TIMESTAMP();
DECLARE paramCount INT DEFAULT 0;

if(storeInHistory > 0) then
  insert into t_monitoring_information
  (subsystem_name,parameter_name,parameter_value,timestamp)
  values (subsystemName, paramName, paramValue,currentTime);
end if;


select count(1) into paramCount from t_recent_monitoring_data
where subsystem_name = subsystemName and parameter_name = paramName;

if(paramCount > 0) then
  update t_recent_monitoring_data
    set
      parameter_value = paramValue,
      timestamp = currentTime
    where subsystem_name = subsystemName
    and parameter_name = paramName;
else
  insert into t_recent_monitoring_data values (subsystemName, paramName, paramValue,currentTime);
end if;

END $$

DELIMITER ;