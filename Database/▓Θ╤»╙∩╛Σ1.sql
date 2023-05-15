--查询某门课程的所有成绩的方差和平均分
select CNO,AVG(FScore) as 平均分,var(FScore) as 方差
from score
group by CNO
having CNO='A1'


--查询某门课程所有选修学生的得分情况
select score.SNO as 学号,NAME as 姓名,FScore as 正考成绩
from score,student
where score.SNO=student.SNO and CNO='A1'
order by(FScore)