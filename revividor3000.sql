-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Nov 04, 2023 at 03:28 AM
-- Server version: 10.4.28-MariaDB
-- PHP Version: 8.2.4

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `revividor3000`
--

-- --------------------------------------------------------

--
-- Table structure for table `devices`
--

CREATE TABLE `devices` (
  `device_id` int(11) NOT NULL,
  `device_name` varchar(250) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- RELATIONSHIPS FOR TABLE `devices`:
--

--
-- Dumping data for table `devices`
--

INSERT INTO `devices` (`device_id`, `device_name`) VALUES
(1, 'temp_dig'),
(2, 'temp_amb'),
(3, 'seg1'),
(4, 'seg2'),
(5, 'rfid'),
(6, 'color');

-- --------------------------------------------------------

--
-- Table structure for table `log_color`
--

CREATE TABLE `log_color` (
  `log_id` int(11) NOT NULL,
  `log_date` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `device_id` int(11) DEFAULT NULL,
  `color` varchar(250) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- RELATIONSHIPS FOR TABLE `log_color`:
--   `device_id`
--       `devices` -> `device_id`
--

-- --------------------------------------------------------

--
-- Table structure for table `log_hum`
--

CREATE TABLE `log_hum` (
  `log_id` int(11) NOT NULL,
  `log_date` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `device_id` int(11) DEFAULT NULL,
  `hum` float DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- RELATIONSHIPS FOR TABLE `log_hum`:
--   `device_id`
--       `devices` -> `device_id`
--

-- --------------------------------------------------------

--
-- Table structure for table `log_seg1`
--

CREATE TABLE `log_seg1` (
  `log_id` int(11) NOT NULL,
  `log_date` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `device_id` int(11) DEFAULT NULL,
  `dato_linea` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- RELATIONSHIPS FOR TABLE `log_seg1`:
--   `device_id`
--       `devices` -> `device_id`
--

-- --------------------------------------------------------

--
-- Table structure for table `log_seg2`
--

CREATE TABLE `log_seg2` (
  `log_id` int(11) NOT NULL,
  `log_date` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `device_id` int(11) DEFAULT NULL,
  `dato_linea` int(11) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- RELATIONSHIPS FOR TABLE `log_seg2`:
--   `device_id`
--       `devices` -> `device_id`
--

-- --------------------------------------------------------

--
-- Table structure for table `log_tag`
--

CREATE TABLE `log_tag` (
  `log_id` int(11) NOT NULL,
  `log_date` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `status` varchar(250) DEFAULT NULL,
  `device_id` int(11) DEFAULT NULL,
  `tag` varchar(250) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- RELATIONSHIPS FOR TABLE `log_tag`:
--   `device_id`
--       `devices` -> `device_id`
--   `tag`
--       `paciente` -> `tag`
--

-- --------------------------------------------------------

--
-- Table structure for table `log_temp`
--

CREATE TABLE `log_temp` (
  `log_id` int(11) NOT NULL,
  `log_date` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `device_id` int(11) DEFAULT NULL,
  `temp` float DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- RELATIONSHIPS FOR TABLE `log_temp`:
--   `device_id`
--       `devices` -> `device_id`
--

-- --------------------------------------------------------

--
-- Table structure for table `log_tempdig`
--

CREATE TABLE `log_tempdig` (
  `log_id` int(11) NOT NULL,
  `log_date` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `device_id` int(11) DEFAULT NULL,
  `temp` float DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- RELATIONSHIPS FOR TABLE `log_tempdig`:
--   `device_id`
--       `devices` -> `device_id`
--

-- --------------------------------------------------------

--
-- Table structure for table `paciente`
--

CREATE TABLE `paciente` (
  `tag` varchar(250) NOT NULL,
  `nombre` varchar(250) DEFAULT NULL,
  `log_date` timestamp NOT NULL DEFAULT current_timestamp() ON UPDATE current_timestamp(),
  `edad` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

--
-- RELATIONSHIPS FOR TABLE `paciente`:
--

--
-- Indexes for dumped tables
--

--
-- Indexes for table `devices`
--
ALTER TABLE `devices`
  ADD PRIMARY KEY (`device_id`);

--
-- Indexes for table `log_color`
--
ALTER TABLE `log_color`
  ADD PRIMARY KEY (`log_id`),
  ADD KEY `device_id` (`device_id`);

--
-- Indexes for table `log_hum`
--
ALTER TABLE `log_hum`
  ADD PRIMARY KEY (`log_id`),
  ADD KEY `device_id` (`device_id`);

--
-- Indexes for table `log_seg1`
--
ALTER TABLE `log_seg1`
  ADD PRIMARY KEY (`log_id`),
  ADD KEY `device_id` (`device_id`);

--
-- Indexes for table `log_seg2`
--
ALTER TABLE `log_seg2`
  ADD PRIMARY KEY (`log_id`),
  ADD KEY `device_id` (`device_id`);

--
-- Indexes for table `log_tag`
--
ALTER TABLE `log_tag`
  ADD PRIMARY KEY (`log_id`),
  ADD KEY `device_id` (`device_id`),
  ADD KEY `tag` (`tag`);

--
-- Indexes for table `log_temp`
--
ALTER TABLE `log_temp`
  ADD PRIMARY KEY (`log_id`),
  ADD KEY `device_id` (`device_id`);

--
-- Indexes for table `log_tempdig`
--
ALTER TABLE `log_tempdig`
  ADD PRIMARY KEY (`log_id`),
  ADD KEY `device_id` (`device_id`);

--
-- Indexes for table `paciente`
--
ALTER TABLE `paciente`
  ADD PRIMARY KEY (`tag`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `devices`
--
ALTER TABLE `devices`
  MODIFY `device_id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;

--
-- AUTO_INCREMENT for table `log_color`
--
ALTER TABLE `log_color`
  MODIFY `log_id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `log_hum`
--
ALTER TABLE `log_hum`
  MODIFY `log_id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `log_seg1`
--
ALTER TABLE `log_seg1`
  MODIFY `log_id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `log_seg2`
--
ALTER TABLE `log_seg2`
  MODIFY `log_id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `log_tag`
--
ALTER TABLE `log_tag`
  MODIFY `log_id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `log_temp`
--
ALTER TABLE `log_temp`
  MODIFY `log_id` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT for table `log_tempdig`
--
ALTER TABLE `log_tempdig`
  MODIFY `log_id` int(11) NOT NULL AUTO_INCREMENT;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `log_color`
--
ALTER TABLE `log_color`
  ADD CONSTRAINT `log_color_ibfk_1` FOREIGN KEY (`device_id`) REFERENCES `devices` (`device_id`);

--
-- Constraints for table `log_hum`
--
ALTER TABLE `log_hum`
  ADD CONSTRAINT `log_hum_ibfk_1` FOREIGN KEY (`device_id`) REFERENCES `devices` (`device_id`);

--
-- Constraints for table `log_seg1`
--
ALTER TABLE `log_seg1`
  ADD CONSTRAINT `log_seg1_ibfk_1` FOREIGN KEY (`device_id`) REFERENCES `devices` (`device_id`);

--
-- Constraints for table `log_seg2`
--
ALTER TABLE `log_seg2`
  ADD CONSTRAINT `log_seg2_ibfk_1` FOREIGN KEY (`device_id`) REFERENCES `devices` (`device_id`);

--
-- Constraints for table `log_tag`
--
ALTER TABLE `log_tag`
  ADD CONSTRAINT `log_tag_ibfk_1` FOREIGN KEY (`device_id`) REFERENCES `devices` (`device_id`),
  ADD CONSTRAINT `log_tag_ibfk_2` FOREIGN KEY (`tag`) REFERENCES `paciente` (`tag`);

--
-- Constraints for table `log_temp`
--
ALTER TABLE `log_temp`
  ADD CONSTRAINT `log_temp_ibfk_1` FOREIGN KEY (`device_id`) REFERENCES `devices` (`device_id`);

--
-- Constraints for table `log_tempdig`
--
ALTER TABLE `log_tempdig`
  ADD CONSTRAINT `log_tempdig_ibfk_1` FOREIGN KEY (`device_id`) REFERENCES `devices` (`device_id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
