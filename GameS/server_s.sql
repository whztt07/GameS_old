-- phpMyAdmin SQL Dump
-- version 3.5.1
-- http://www.phpmyadmin.net
--
-- Хост: localhost
-- Время создания: Сен 16 2016 г., 17:34
-- Версия сервера: 5.5.25
-- Версия PHP: 5.3.13

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- База данных: `server_s`
--

-- --------------------------------------------------------

--
-- Структура таблицы `baseitem`
--

CREATE TABLE IF NOT EXISTS `baseitem` (
  `itemId` int(11) NOT NULL AUTO_INCREMENT,
  `type` text NOT NULL,
  `stack` tinyint(1) NOT NULL DEFAULT '0',
  `weight` float NOT NULL DEFAULT '0.1',
  `subtype` text NOT NULL,
  `minAttack` float NOT NULL DEFAULT '0',
  `maxAttack` float NOT NULL DEFAULT '0',
  `rangeAttack` float NOT NULL DEFAULT '0',
  `accuracy` float NOT NULL DEFAULT '0',
  `attackSpeed` float NOT NULL DEFAULT '0',
  `critChance` int(11) NOT NULL DEFAULT '0',
  `critRate` int(11) NOT NULL DEFAULT '0',
  `speedPenalty` int(11) NOT NULL DEFAULT '0',
  `failCastSpell` int(11) NOT NULL DEFAULT '0',
  `resSlash` int(11) NOT NULL DEFAULT '0',
  `resCrush` int(11) NOT NULL DEFAULT '0',
  `resPierce` int(11) NOT NULL DEFAULT '0',
  `evasionPenalty` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`itemId`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=16 ;

--
-- Дамп данных таблицы `baseitem`
--

INSERT INTO `baseitem` (`itemId`, `type`, `stack`, `weight`, `subtype`, `minAttack`, `maxAttack`, `rangeAttack`, `accuracy`, `attackSpeed`, `critChance`, `critRate`, `speedPenalty`, `failCastSpell`, `resSlash`, `resCrush`, `resPierce`, `evasionPenalty`) VALUES
(1, 'Weapon', 0, 4, 'Sword', 1, 5, 1.5, 6, 500, 15, 2, 0, 0, 0, 0, 0, 0),
(2, 'Weapon', 0, 6, 'Blunt', 1, 4, 1.5, 5, 500, 5, 3, 0, 0, 0, 0, 0, 0),
(3, 'Weapon', 0, 2, 'Bow', 1, 5, 6, 4, 400, 10, 2, 0, 0, 0, 0, 0, 0),
(4, 'Weapon', 0, 4, 'Sword', 4, 10, 1.5, 6, 500, 15, 2, 0, 0, 0, 0, 0, 0),
(5, 'Weapon', 0, 6, 'Blunt', 4, 8, 1.5, 5, 500, 5, 3, 0, 0, 0, 0, 0, 0),
(6, 'Weapon', 0, 2, 'Bow', 4, 10, 6, 4, 400, 10, 2, 0, 0, 0, 0, 0, 0),
(7, 'Armor', 0, 2, '', 0, 0, 0, 0, 0, 0, 0, 0, 5, 2, 2, 1, 7),
(8, 'Armor', 0, 5, '', 0, 0, 0, 0, 0, 0, 0, 8, 25, 2, 2, 4, 4),
(9, 'Armor', 0, 12, '', 0, 0, 0, 0, 0, 0, 0, 15, 45, 6, 3, 3, 1),
(10, 'Armor', 0, 2, '', 0, 0, 0, 0, 0, 0, 0, 0, 5, 4, 4, 2, 7),
(11, 'Armor', 0, 5, '', 0, 0, 0, 0, 0, 0, 0, 8, 25, 4, 4, 8, 4),
(12, 'Armor', 0, 12, '', 0, 0, 0, 0, 0, 0, 0, 15, 45, 12, 6, 6, 1),
(13, 'Potion', 1, 0.1, 'HP', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(14, 'Potion', 1, 0.1, 'MP', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(15, 'Gold', 1, 0.01, '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Структура таблицы `basepers`
--

CREATE TABLE IF NOT EXISTS `basepers` (
  `id` int(11) NOT NULL,
  `name` text NOT NULL,
  `race` int(11) NOT NULL,
  `curHP` float NOT NULL,
  `curMP` float NOT NULL,
  `strength` int(11) NOT NULL,
  `agility` int(11) NOT NULL,
  `constitution` int(11) NOT NULL,
  `intelligence` int(11) NOT NULL,
  `wisdom` int(11) NOT NULL,
  `visibleRange` float NOT NULL,
  `weaponSlot` int(11) NOT NULL,
  `bodySlot` int(11) NOT NULL,
  `freeCharacteristics` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Дамп данных таблицы `basepers`
--

INSERT INTO `basepers` (`id`, `name`, `race`, `curHP`, `curMP`, `strength`, `agility`, `constitution`, `intelligence`, `wisdom`, `visibleRange`, `weaponSlot`, `bodySlot`, `freeCharacteristics`) VALUES
(0, 'Human', 0, 100, 200, 10, 10, 10, 10, 10, 20, -1, -1, 10),
(1, 'Swordsman Novice', 1, 100, 200, 14, 14, 12, 10, 10, 18, 0, 7, 0);

-- --------------------------------------------------------

--
-- Структура таблицы `buff`
--

CREATE TABLE IF NOT EXISTS `buff` (
  `persId` int(11) NOT NULL AUTO_INCREMENT,
  `slot0` int(11) NOT NULL DEFAULT '-1',
  `levelSlot0` int(11) NOT NULL DEFAULT '1',
  `time0` float NOT NULL DEFAULT '0',
  `slot1` int(11) NOT NULL DEFAULT '-1',
  `levelSlot1` int(11) NOT NULL DEFAULT '1',
  `time1` float NOT NULL DEFAULT '0',
  `slot2` int(11) NOT NULL DEFAULT '-1',
  `levelSlot2` int(11) NOT NULL DEFAULT '1',
  `time2` float NOT NULL DEFAULT '0',
  `slot3` int(11) NOT NULL DEFAULT '-1',
  `levelSlot3` int(11) NOT NULL DEFAULT '1',
  `time3` float NOT NULL DEFAULT '0',
  `slot4` int(11) NOT NULL DEFAULT '-1',
  `levelSlot4` int(11) NOT NULL DEFAULT '1',
  `time4` float NOT NULL DEFAULT '0',
  `slot5` int(11) NOT NULL DEFAULT '-1',
  `levelSlot5` int(11) NOT NULL DEFAULT '1',
  `time5` float NOT NULL DEFAULT '0',
  `slot6` int(11) NOT NULL DEFAULT '-1',
  `levelSlot6` int(11) NOT NULL DEFAULT '1',
  `time6` float NOT NULL DEFAULT '0',
  `slot7` int(11) NOT NULL DEFAULT '-1',
  `levelSlot7` int(11) NOT NULL DEFAULT '1',
  `time7` float NOT NULL DEFAULT '0',
  `slot8` int(11) NOT NULL DEFAULT '-1',
  `levelSlot8` int(11) NOT NULL DEFAULT '1',
  `time8` float NOT NULL DEFAULT '0',
  `slot9` int(11) NOT NULL DEFAULT '-1',
  `levelSlot9` int(11) NOT NULL DEFAULT '1',
  `time9` float NOT NULL DEFAULT '0',
  PRIMARY KEY (`persId`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=8 ;

--
-- Дамп данных таблицы `buff`
--

INSERT INTO `buff` (`persId`, `slot0`, `levelSlot0`, `time0`, `slot1`, `levelSlot1`, `time1`, `slot2`, `levelSlot2`, `time2`, `slot3`, `levelSlot3`, `time3`, `slot4`, `levelSlot4`, `time4`, `slot5`, `levelSlot5`, `time5`, `slot6`, `levelSlot6`, `time6`, `slot7`, `levelSlot7`, `time7`, `slot8`, `levelSlot8`, `time8`, `slot9`, `levelSlot9`, `time9`) VALUES
(1, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0),
(2, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0),
(3, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0),
(4, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0),
(6, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0),
(7, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0, -1, 1, 0);

-- --------------------------------------------------------

--
-- Структура таблицы `debuff`
--

CREATE TABLE IF NOT EXISTS `debuff` (
  `persId` int(11) NOT NULL AUTO_INCREMENT,
  `slot0` int(11) NOT NULL DEFAULT '-1',
  `levelSlot0` int(11) NOT NULL DEFAULT '1',
  `time0` float NOT NULL DEFAULT '0',
  `slot1` int(11) NOT NULL DEFAULT '-1',
  `levelSlot1` int(11) NOT NULL DEFAULT '1',
  `time1` float NOT NULL DEFAULT '0',
  `slot2` int(11) NOT NULL DEFAULT '-1',
  `levelSlot2` int(11) NOT NULL DEFAULT '1',
  `time2` float NOT NULL DEFAULT '0',
  `slot3` int(11) NOT NULL DEFAULT '-1',
  `levelSlot3` int(11) NOT NULL DEFAULT '1',
  `time3` float NOT NULL DEFAULT '0',
  `slot4` int(11) NOT NULL DEFAULT '-1',
  `levelSlot4` int(11) NOT NULL DEFAULT '1',
  `time4` float NOT NULL DEFAULT '0',
  `slot5` int(11) NOT NULL DEFAULT '-1',
  `levelSlot5` int(11) NOT NULL DEFAULT '1',
  `time5` float NOT NULL DEFAULT '0',
  `slot6` int(11) NOT NULL DEFAULT '-1',
  `levelSlot6` int(11) NOT NULL DEFAULT '1',
  `time6` float NOT NULL DEFAULT '0',
  `slot7` int(11) NOT NULL DEFAULT '-1',
  `levelSlot7` int(11) NOT NULL DEFAULT '1',
  `time7` float NOT NULL DEFAULT '0',
  `slot8` int(11) NOT NULL DEFAULT '-1',
  `levelSlot8` int(11) NOT NULL DEFAULT '1',
  `time8` float NOT NULL DEFAULT '0',
  `slot9` int(11) NOT NULL DEFAULT '-1',
  `levelSlot9` int(11) NOT NULL DEFAULT '1',
  `time9` float NOT NULL DEFAULT '0',
  PRIMARY KEY (`persId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Структура таблицы `inventory`
--

CREATE TABLE IF NOT EXISTS `inventory` (
  `persId` int(11) NOT NULL AUTO_INCREMENT,
  `slot0` int(11) NOT NULL DEFAULT '-1',
  `count0` int(11) NOT NULL DEFAULT '0',
  `slot1` int(11) NOT NULL DEFAULT '-1',
  `count1` int(11) NOT NULL DEFAULT '0',
  `slot2` int(11) NOT NULL DEFAULT '-1',
  `count2` int(11) NOT NULL DEFAULT '0',
  `slot3` int(11) NOT NULL DEFAULT '-1',
  `count3` int(11) NOT NULL DEFAULT '0',
  `slot4` int(11) NOT NULL DEFAULT '-1',
  `count4` int(11) NOT NULL DEFAULT '0',
  `slot5` int(11) NOT NULL DEFAULT '-1',
  `count5` int(11) NOT NULL DEFAULT '0',
  `slot6` int(11) NOT NULL DEFAULT '-1',
  `count6` int(11) NOT NULL DEFAULT '0',
  `slot7` int(11) NOT NULL DEFAULT '-1',
  `count7` int(11) NOT NULL DEFAULT '0',
  `slot8` int(11) NOT NULL DEFAULT '-1',
  `count8` int(11) NOT NULL DEFAULT '0',
  `slot9` int(11) NOT NULL DEFAULT '-1',
  `count9` int(11) NOT NULL DEFAULT '0',
  `slot10` int(11) NOT NULL DEFAULT '-1',
  `count10` int(11) NOT NULL DEFAULT '0',
  `slot11` int(11) NOT NULL DEFAULT '-1',
  `count11` int(11) NOT NULL DEFAULT '0',
  `slot12` int(11) NOT NULL DEFAULT '-1',
  `count12` int(11) NOT NULL DEFAULT '0',
  `slot13` int(11) NOT NULL DEFAULT '-1',
  `count13` int(11) NOT NULL DEFAULT '0',
  `slot14` int(11) NOT NULL DEFAULT '-1',
  `count14` int(11) NOT NULL DEFAULT '0',
  `slot15` int(11) NOT NULL DEFAULT '-1',
  `count15` int(11) NOT NULL DEFAULT '0',
  `slot16` int(11) NOT NULL DEFAULT '-1',
  `count16` int(11) NOT NULL DEFAULT '0',
  `slot17` int(11) NOT NULL DEFAULT '-1',
  `count17` int(11) NOT NULL DEFAULT '0',
  `slot18` int(11) NOT NULL DEFAULT '-1',
  `count18` int(11) NOT NULL DEFAULT '0',
  `slot19` int(11) NOT NULL DEFAULT '-1',
  `count19` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`persId`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=8 ;

--
-- Дамп данных таблицы `inventory`
--

INSERT INTO `inventory` (`persId`, `slot0`, `count0`, `slot1`, `count1`, `slot2`, `count2`, `slot3`, `count3`, `slot4`, `count4`, `slot5`, `count5`, `slot6`, `count6`, `slot7`, `count7`, `slot8`, `count8`, `slot9`, `count9`, `slot10`, `count10`, `slot11`, `count11`, `slot12`, `count12`, `slot13`, `count13`, `slot14`, `count14`, `slot15`, `count15`, `slot16`, `count16`, `slot17`, `count17`, `slot18`, `count18`, `slot19`, `count19`) VALUES
(1, 1, 1, 7, 1, 13, 5, 12, 5, 2, 1, 8, 1, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0),
(2, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0),
(3, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0),
(4, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0),
(6, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0),
(7, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0);

-- --------------------------------------------------------

--
-- Структура таблицы `pers`
--

CREATE TABLE IF NOT EXISTS `pers` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `accId` int(11) NOT NULL,
  `name` text NOT NULL,
  `race` int(11) NOT NULL DEFAULT '0',
  `pos_x` float NOT NULL DEFAULT '0',
  `pos_y` float NOT NULL DEFAULT '0',
  `pos_z` float NOT NULL DEFAULT '0',
  `rot_y` float NOT NULL DEFAULT '0',
  `live` tinyint(1) NOT NULL DEFAULT '1',
  `resInPlace` tinyint(1) NOT NULL DEFAULT '0',
  `corpSaveTime` float NOT NULL DEFAULT '0',
  `curHP` float NOT NULL DEFAULT '0',
  `curMP` float NOT NULL DEFAULT '0',
  `strength` int(11) NOT NULL DEFAULT '10',
  `agility` int(11) NOT NULL DEFAULT '10',
  `constitution` int(11) NOT NULL DEFAULT '10',
  `intelligence` int(11) NOT NULL DEFAULT '10',
  `wisdom` int(11) NOT NULL DEFAULT '10',
  `freeCharacteristics` int(11) NOT NULL DEFAULT '10',
  `weaponSlot` int(11) NOT NULL DEFAULT '-1',
  `bodySlot` int(11) NOT NULL DEFAULT '-1',
  `visibleRange` float NOT NULL DEFAULT '20',
  `characteristicPoint` int(11) NOT NULL DEFAULT '0',
  `abilityPoint` int(11) NOT NULL DEFAULT '0',
  `spellPoint` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=8 ;

--
-- Дамп данных таблицы `pers`
--

INSERT INTO `pers` (`id`, `accId`, `name`, `race`, `pos_x`, `pos_y`, `pos_z`, `rot_y`, `live`, `resInPlace`, `corpSaveTime`, `curHP`, `curMP`, `strength`, `agility`, `constitution`, `intelligence`, `wisdom`, `freeCharacteristics`, `weaponSlot`, `bodySlot`, `visibleRange`, `characteristicPoint`, `abilityPoint`, `spellPoint`) VALUES
(1, 1, 'gur', 0, 0, 0, 0, 0, 1, 0, 0, 1, 2, 10, 10, 10, 10, 10, 50, 3, 6, 20, 0, 0, 0),
(2, 1, 'gures', 0, 0, 0, 0, 0, 1, 0, 0, 100, 200, 10, 10, 10, 10, 10, 10, -1, -1, 20, 0, 0, 0),
(3, 1, 'gure', 0, 0, 0, 0, 0, 1, 0, 0, 100, 200, 10, 10, 10, 10, 10, 10, -1, -1, 20, 0, 0, 0),
(4, 1, 'yer', 0, 0, 0, 0, 0, 1, 0, 0, 100, 200, 10, 10, 10, 10, 10, 10, -1, -1, 20, 0, 0, 0),
(6, 3, 'ert', 0, 0, 0, 0, 0, 1, 0, 0, 100, 200, 10, 10, 10, 10, 10, 10, -1, -1, 20, 0, 0, 0),
(7, 1, 'tiny', 0, 0, 0, 0, 0, 1, 0, 0, 100, 200, 10, 10, 10, 10, 10, 10, -1, -1, 20, 0, 0, 0);

-- --------------------------------------------------------

--
-- Структура таблицы `users`
--

CREATE TABLE IF NOT EXISTS `users` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `login` text NOT NULL,
  `pass` text NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=4 ;

--
-- Дамп данных таблицы `users`
--

INSERT INTO `users` (`id`, `login`, `pass`) VALUES
(1, 'qwerty', 'fghfgh'),
(2, 'dds', 'sd'),
(3, 'qwertyq', 'fghfgh');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
