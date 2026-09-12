UPDATE `creature_template` SET `AIName`='SmartAI', `ScriptName`='' WHERE `entry`=91462;
DELETE FROM `smart_scripts` WHERE `entryorguid`=91462;
INSERT INTO `smart_scripts` (`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, `event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, `event_param5`, `event_param_string`, `action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, `target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, `comment`) VALUES 
(91462, 0, 0, 1, 62, 0, 100, 1, 18273, 0, 0, 0, 0, '', 11, 181481, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'Malfurion Stormrage - On Gossip Select - Cast Summon Spell'),
(91462, 0, 1, 0, 61, 0, 100, 1, 0, 0, 0, 0, 0, '', 72, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 'Malfurion Stormrage - Link - Close Gossip');

