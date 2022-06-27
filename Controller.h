#pragma once
#ifndef CONTROLLERS_DEF

#define CONTROLLERS_DEF

// the controllers for all the window

/**
 * \brief the start window controller
 */
void IndexController();

/**
 * \brief student info window controller
 */
void StudentInfoController();

/**
 * \brief score manager window controller
 */
void ScoreManagerController();

/**
 * \brief data statistic controller
 * \param sort_lesson_list the data list
 */
 void DataController(const SortLessonList* sort_lesson_list);

#endif

