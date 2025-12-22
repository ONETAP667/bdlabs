### 1. Для кожного курсу знайти в якому мінімальному семестрі він може читатись.

**Код SQL:**

```
WITH RECURSIVE course_semester AS (
    SELECT
        c.course_id,
        c.name,
        1 AS min_semester
    FROM course c
    LEFT JOIN course_prerequisite cp
        ON cp.course_id = c.course_id
    WHERE cp.course_id IS NULL

    UNION ALL

    SELECT
        c.course_id,
        c.name,
        cs.min_semester + 1 AS min_semester
    FROM course c
    JOIN course_prerequisite cp
        ON cp.course_id = c.course_id
    JOIN course_semester cs
        ON cs.course_id = cp.prerequisite_course_id
)
SELECT
    course_id,
    name,
    MAX(min_semester) AS minimal_semester
FROM course_semester
GROUP BY course_id, name
ORDER BY minimal_semester, name;
```

**Тут:**
* course_id - ID курсу
* name - Ім'я курсу
* minimal_semester - Мінімальний семестр

**Скріншот:**
<img width="2560" alt="scr1" src="https://github.com/ONETAP667/bdlabs/blob/main/ex/screx2/scr1.png">

### 2. Знайти всіх студентів, які записані на більше курсів ніж в середньому

**Код SQL:**

```
WITH courses_per_student AS (
    SELECT
        s.student_id,
        s.name,
        s.surname,
        g.name AS group_name,
        COUNT(e.course_id) AS courses_count
    FROM student s
    LEFT JOIN enrolment e ON e.student_id = s.student_id
    JOIN student_group g ON g.group_id = s.group_id
    GROUP BY s.student_id, s.name, s.surname, g.name
),
avg_courses AS (
    SELECT AVG(courses_count) AS avg_courses
    FROM courses_per_student
)
SELECT
    cps.student_id,
    cps.name,
    cps.surname,
    cps.group_name,
    cps.courses_count
FROM courses_per_student cps
CROSS JOIN avg_courses a
WHERE cps.courses_count > a.avg_courses
ORDER BY cps.courses_count DESC, cps.surname;
```

**Тут:**
* student_id - ID студента
* name, surname - Імʼя та прізвище
* group_name - Група
* courses_count - Кількість курсів, на які записаний студент

**Скріншот:**
<img width="2560" alt="scr2" src="https://github.com/ONETAP667/bdlabs/blob/main/ex/screx2/scr2.png">


### 3.  Знайти топ-3 студентів у кожному курсі за отриманими балами

**Код SQL:**

```
SELECT
    course_name,
    student_id,
    student_name,
    student_surname,
    grade,
    rank_in_course
FROM (
    SELECT
        c.course_id,
        c.name AS course_name,
        s.student_id,
        s.name AS student_name,
        s.surname AS student_surname,
        e.grade,
        RANK() OVER (
            PARTITION BY c.course_id
            ORDER BY e.grade DESC
        ) AS rank_in_course
    FROM enrolment e
    JOIN course c  ON c.course_id = e.course_id
    JOIN student s ON s.student_id = e.student_id
    WHERE e.grade IS NOT NULL
) ranked
WHERE rank_in_course <= 3
ORDER BY course_name, rank_in_course, student_surname;
```

**Тут:**
* course_name - Назва курсу
* student_id - ID студента
* student_name, student_surname - Імʼя та прізвище
* grade - Отриманий бал
* rank_in_course - Місце студента в межах курсу

**Скріншот:**
<img width="2560" alt="scr3" src="https://github.com/ONETAP667/bdlabs/blob/main/ex/screx2/scr3.png">
