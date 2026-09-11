UPDATE `creature_template` SET `VehicleId`=4120 WHERE `entry`=91465;
UPDATE `creature_template` SET `VehicleId`=91465 WHERE `entry`=94588;

DELETE FROM `vehicle_template_accessory` WHERE (`entry`=91465 AND `seat_id`=1);
INSERT INTO `vehicle_template_accessory` (`entry`, `accessory_entry`, `seat_id`, `minion`, `description`, `summontype`, `summontimer`) VALUES
(91465, 94588, 1, 0, '91465 - 94588', 0, 0); -- 91465 - 94588

DELETE FROM `creature_text` WHERE `CreatureID`=94588 AND `GroupID` IN (0, 1, 2, 3, 4, 5);
DELETE FROM `creature_text` WHERE `CreatureID`=91465;
INSERT INTO `creature_text` (`CreatureID`, `GroupID`, `ID`, `Text`, `Type`, `Language`, `Probability`, `Emote`, `Duration`, `Sound`, `BroadcastTextId`, `TextRange`, `comment`) VALUES
(91465, 0, 0, 'Follow me.', 12, 0, 100, 0, 0, 52741, 0, 0, 'Malfurion Stormrage to Player'),
(94588, 0, 0, 'Ahh, Val\'sharah...', 12, 0, 100, 1, 0, 52735, 0, 0, 'Malfurion Stormrage to Malfurion Stormrage'),
(94588, 1, 1, 'Every step in this forest brings back precious memories.', 12, 0, 100, 0, 0, 52358, 0, 0, 'Malfurion Stormrage to Malfurion Stormrage'),
(94588, 2, 2, 'Ages ago, the first druids molded this land to be a reflection of the Emerald Dream.', 12, 0, 100, 0, 0, 52359, 0, 0, 'Malfurion Stormrage to Malfurion Stormrage'),
(94588, 3, 3, 'Merely an echo, but Val\'sharah is as close to the Dream as this world can come.', 12, 0, 100, 0, 0, 52360, 0, 0, 'Malfurion Stormrage to Malfurion Stormrage'),
(94588, 4, 4, 'Make ready, hero. We shall soon stand in the presence of the Lord of the Forest.', 12, 0, 100, 0, 0, 52277, 0, 0, 'Malfurion Stormrage to Malfurion Stormrage');
