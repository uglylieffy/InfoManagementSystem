
--ѧ����Ϣ
select *
from student
where SNO='10001'


--��ѯĩ��ѧ���ĸ��ſεĳɼ�
select course.CNO,CNAME,FScore,SScore,LScore
from student,score,course
where student.SNO=score.SNO AND
      score.CNO=course.CNO and
      student.SNO=10001 
--ƽ���ֳɼ�
select VAR(FScore) as ����,AVG(FScore) AS ƽ����
from score
WHERE SNO=10001


--��ѯĳ��ѧ����ѡ������γ̵�������ƽ����
select CTYPE AS ѡ������,count(*) as ѡ������,avg(FScore) as ƽ����
from score a,course b
where a.CNO=b.CNO and SNO=10001 and (a.FScore>60 or b.CTYPE<>'��ѡ')
group by CTYPE


create view view_1(score.CNO,  as 
select *
from score,course
where score.CNO=course.CNO 
  
