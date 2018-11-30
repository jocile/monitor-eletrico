CREATE TABLE `teste`.`eletrico` (
 `id` INT NOT NULL AUTO_INCREMENT ,
  `data` DATE NOT NULL ,
   `hora` TIME NOT NULL ,
    `corrente` FLOAT NOT NULL ,
     PRIMARY KEY (`id`)) ENGINE = InnoDB;

INSERT INTO `eletrico` (`id`, `data`, `hora`, `corrente`) VALUES
  (NULL, '2018-11-20', '07:00:00', '1'),
  (NULL, '2018-11-20', '08:00:00', '0.9'),
  (NULL, '2018-11-20', '09:00:00', '1.1'),
  (NULL, '2018-11-20', '10:00:00', '1.2');
