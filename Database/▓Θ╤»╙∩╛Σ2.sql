
--学生信息
select *
from student
where SNO='10001'


--查询末个学生的各门课的成绩
select course.CNO,CNAME,FScore,SScore,LScore
from student,score,course
where student.SNO=score.SNO AND
      score.CNO=course.CNO and
      student.SNO=10001 
--平均分成绩
select VAR(FScore) as 方差,AVG(FScore) AS 平均分
from score
WHERE SNO=10001


--查询某个学生的选修三类课程的门数和平均分
select CTYPE AS 选课类型,count(*) as 选课门数,avg(FScore) as 平均分
from score a,course b
where a.CNO=b.CNO and SNO=10001 and (a.FScore>60 or b.CTYPE<>'公选')
group by CTYPE


create view view_1(score.CNO,  as 
select *
from score,course
where score.CNO=course.CNO 
  
