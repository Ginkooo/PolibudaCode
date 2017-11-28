-- phpMyAdmin SQL Dump
-- version 4.5.1
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: Nov 24, 2017 at 12:00 PM
-- Server version: 10.1.16-MariaDB
-- PHP Version: 5.6.24

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `biblioteka_pc`
--

-- --------------------------------------------------------

--
-- Table structure for table `books`
--

CREATE TABLE `books` (
  `id` int(11) NOT NULL,
  `title` varchar(70) COLLATE utf8_polish_ci NOT NULL,
  `release_date` date NOT NULL,
  `genre` enum('Adventure','Fantasy','Action','Document','Sci-Fi') COLLATE utf8_polish_ci NOT NULL,
  `author` varchar(70) COLLATE utf8_polish_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `books`
--

INSERT INTO `books` (`id`, `title`, `release_date`, `genre`, `author`) VALUES
(1, 'The Orphan''s Tale', '1995-11-09', 'Fantasy', 'Pam Jenoff'),
(2, 'Knowing God by Name', '2005-11-09', 'Sci-Fi', 'David Wikerson'),
(3, 'The Husband''s Secret', '2010-11-09', '', 'Liane Moriaty'),
(4, 'Grey', '2016-11-09', 'Action', 'E L James'),
(5, 'Four Friends', '2013-11-09', 'Adventure', 'Robyn Carr'),
(6, 'Born a Crime', '2000-11-09', 'Sci-Fi', 'Trevor Noah');

-- --------------------------------------------------------

--
-- Table structure for table `borrows`
--

CREATE TABLE `borrows` (
  `id` int(11) NOT NULL,
  `book` int(11) NOT NULL,
  `student` int(11) NOT NULL,
  `employee` int(11) NOT NULL,
  `borrowing_date` date NOT NULL,
  `date_of_return` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `borrows`
--

INSERT INTO `borrows` (`id`, `book`, `student`, `employee`, `borrowing_date`, `date_of_return`) VALUES
(1, 2, 1, 3, '2017-11-24', '2018-01-24'),
(2, 1, 4, 2, '2017-11-23', '2018-01-24'),
(3, 6, 1, 4, '2017-11-24', '2018-01-24'),
(4, 5, 4, 3, '2017-11-24', '2018-01-24'),
(5, 3, 3, 3, '2017-11-06', '2017-11-15');

-- --------------------------------------------------------

--
-- Table structure for table `employees`
--

CREATE TABLE `employees` (
  `id` int(11) NOT NULL,
  `firstname` varchar(50) COLLATE utf8_polish_ci NOT NULL,
  `lastname` varchar(50) COLLATE utf8_polish_ci NOT NULL,
  `phone_nr` int(9) NOT NULL,
  `pesel` bigint(11) NOT NULL,
  `employment_date` date NOT NULL,
  `birth_date` date NOT NULL,
  `city` varchar(25) COLLATE utf8_polish_ci NOT NULL,
  `street` varchar(70) COLLATE utf8_polish_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `employees`
--

INSERT INTO `employees` (`id`, `firstname`, `lastname`, `phone_nr`, `pesel`, `employment_date`, `birth_date`, `city`, `street`) VALUES
(1, 'Piotr', 'Czajka', 2147483647, 52547421464, '2010-05-11', '1991-09-12', 'Lublin', 'Króla Rogera'),
(2, 'Michał', 'Wawrzyk', 2147483647, 52637485944, '2011-05-11', '1990-09-12', 'Lublin', 'Polna'),
(3, 'Kuba', 'Marcyniuk', 2147483647, 74784632436, '2015-05-11', '1989-09-12', 'Lublin', 'Malinowa'),
(4, 'Michał', 'Wawrzyk', 2147483647, 62859372849, '2014-05-11', '1988-09-12', 'Lublin', 'Jana pawła II');

-- --------------------------------------------------------

--
-- Table structure for table `students`
--

CREATE TABLE `students` (
  `id` int(11) NOT NULL,
  `index_nr` int(5) NOT NULL,
  `firstname` varchar(50) COLLATE utf8_polish_ci NOT NULL,
  `lastname` varchar(50) COLLATE utf8_polish_ci NOT NULL,
  `birth_date` date NOT NULL,
  `pesel` int(11) NOT NULL,
  `city` varchar(25) COLLATE utf8_polish_ci NOT NULL,
  `street` varchar(25) COLLATE utf8_polish_ci NOT NULL,
  `apartment` varchar(5) COLLATE utf8_polish_ci NOT NULL,
  `phone_nr` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `students`
--

INSERT INTO `students` (`id`, `index_nr`, `firstname`, `lastname`, `birth_date`, `pesel`, `city`, `street`, `apartment`, `phone_nr`) VALUES
(1, 8234, 'Piotr', 'Błaszczyk', '1995-04-05', 2147483647, 'Lublin', 'Organowa', '3', 2147483647),
(2, 8234, 'Piotr', 'Kubecki', '1995-04-05', 2147483647, 'Lublin', 'Braci Wieniawskich', '1', 2147483647),
(3, 8234, 'Michał', 'Błaszczyk', '1996-04-04', 2147483647, 'Lublin', 'Organowa', '3', 2147483647),
(4, 8234, 'Kuba', 'Marcyniuk', '1993-04-05', 2147483647, 'Lublin', 'Organowa', '3', 2147483647),
(5, 8234, 'Filip', 'Demski', '1996-04-11', 2147483647, 'Lublin', 'Organowa', '3', 2147483647),
(6, 8234, 'Kuba', 'Marcyniuk', '1997-07-05', 2147483647, 'Lublin', 'Magnoliowa', '64', 2147483647);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `books`
--
ALTER TABLE `books`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `borrows`
--
ALTER TABLE `borrows`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `book` (`book`);

--
-- Indexes for table `employees`
--
ALTER TABLE `employees`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `students`
--
ALTER TABLE `students`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `books`
--
ALTER TABLE `books`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;
--
-- AUTO_INCREMENT for table `borrows`
--
ALTER TABLE `borrows`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;
--
-- AUTO_INCREMENT for table `employees`
--
ALTER TABLE `employees`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;
--
-- AUTO_INCREMENT for table `students`
--
ALTER TABLE `students`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
