--根据班号查询该班的不及格学生的记录
create view view_bujige as
select student.SNO,NAME ,course.CNO,CNAME,FScore
from student,score,course
where student.SNO=score.SNO and score.CNO=course.CNO and CLNO='16CS1' and FScore<60

--统计该班级不及格总人数
create view view_bujige2 as
select distinct SNO
from view_bujige

select count(*)as 此班级中不及格人数
from view_bujige2

