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

// todo waiting for test
/**
 * \brief search a student's score
 */
void SearchScoreByStudent();

// todo waiting for test
/**
 * \brief search the score of some lesson
 */
void SearchScoreByLesson();

// todo waiting for test
void UpdateStudentScore();

// todo waiting for test
void AddLessonForStudent();

#endif

