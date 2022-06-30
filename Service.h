#pragma once

#ifndef SERVICE_DEF

#define SERVICE_DEF

/**
 * \brief handle the service to add student to data
 */
void AddStudent();

/**
 * \brief handle the service to delete student
 */
void DeleteStudent();

/**
 * \brief search student info and show it
 */
void SearchStudent();

/**
 * \brief show all the student data
 */
void ShowAllStudent();

/**
 * \brief update a student info
 */
void UpdateStudentInfo();

/**
 * \brief search all score and show
 */
void SearchAllScore();

/**
 * \brief search a student's score
 */
void SearchScoreByStudent();

/**
 * \brief search the score of some lesson
 */
void SearchScoreByLesson();

/**
 * \brief update the score of a student by id
 */
void UpdateStudentScore();

/**
 * \brief add a lesson for student by class or id
 */
void AddLessonForStudent();

#endif

