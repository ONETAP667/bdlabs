### 1. Порахувати успішність студентів залежно від року навчання

**Код SQL:**

```
SELECT
    c.student_year                         AS study_year,
    COUNT(e.grade)                         AS graded_count,
    ROUND(AVG(e.grade), 2)                 AS avg_grade,
    COUNT(CASE WHEN e.grade >= 60 THEN 1 END) AS passed_count,
    COUNT(CASE WHEN e.grade < 60 THEN 1 END)  AS failed_count,
    ROUND(
        COUNT(CASE WHEN e.grade >= 60 THEN 1 END)::numeric
        / NULLIF(COUNT(e.grade), 0) * 100,
        2
    ) AS success_percent
FROM course c
JOIN enrolment e ON e.course_id = c.course_id
WHERE e.grade IS NOT NULL
GROUP BY c.student_year.3
ORDER BY c.student_year;
```

**Тут:**
study_year - Рік навчання
graded_count - Кількість виставлених оцінок
avg_grade - Середній бал
passed_count - Кількість складених дисциплін
failed_count - Кількість не складених
success_percent - Відсоток успішності

**Скріншот:**
<img width="2560" alt="scr1" src="https://github.com/ONETAP667/bdlabs/blob/main/ex/screx1/scr1.png">

### 2. Для кожного з студентів знайти його середній бал у порівнянні з середнім балом по групі

**Код SQL:**

```
WITH student_avg AS (
    SELECT
        s.student_id,
        s.group_id,
        AVG(e.grade) AS student_avg_grade
    FROM student s
    JOIN enrolment e ON e.student_id = s.student_id
    WHERE e.grade IS NOT NULL
    GROUP BY s.student_id, s.group_id
),
group_avg AS (
    SELECT
        s.group_id,
        AVG(e.grade) AS group_avg_grade
    FROM student s
    JOIN enrolment e ON e.student_id = s.student_id
    WHERE e.grade IS NOT NULL
    GROUP BY s.group_id
)
SELECT
    s.student_id,
    s.name,
    s.surname,
    g.name AS group_name,
    ROUND(sa.student_avg_grade, 2) AS student_avg_grade,
    ROUND(ga.group_avg_grade, 2)   AS group_avg_grade,
    ROUND(sa.student_avg_grade - ga.group_avg_grade, 2) AS diff_from_group
FROM student_avg sa
JOIN group_avg ga ON ga.group_id = sa.group_id
JOIN student s ON s.student_id = sa.student_id
JOIN student_group g ON g.group_id = s.group_id
ORDER BY g.name, s.surname;
```

**Тут:**
student_id - ID студента
name, surname - Імʼя та прізвище
group_name - Назва групи
student_avg_grade - Середній бал студента
group_avg_grade - Середній бал групи
diff_from_group - Різниця від середнього балу групи

**Скріншот:**
<img width="2560" alt="scr2" src="https://github.com/ONETAP667/bdlabs/blob/main/ex/screx1/scr2.png">

### 3. Порахувати статистику записів на курси для кожного року навчання: кількість курсів, кількість записів, кількість студентів що вже отримали бали

**Код SQL:**
```
SELECT
    c.student_year                                   AS study_year,
    COUNT(DISTINCT c.course_id)                      AS courses_count,
    COUNT(e.student_id)                              AS enrolments_count,
    COUNT(DISTINCT CASE 
        WHEN e.grade IS NOT NULL THEN e.student_id 
    END)                                             AS students_with_grades
FROM course c
LEFT JOIN enrolment e ON e.course_id = c.course_id
GROUP BY c.student_year
ORDER BY c.student_year;
```

**Тут:**

study_year - рік навчання
courses_count - кількість курсів
enrolments_count - кількість записів
students_with_grades - кількість студентів, що вже отримали бали

**Скріншот:**
<img width="2560" alt="scr3" src="https://github.com/ONETAP667/bdlabs/blob/main/ex/screx1/scr3.png">
