--���ݰ�Ų�ѯ�ð�Ĳ�����ѧ���ļ�¼
create view view_bujige as
select student.SNO,NAME ,course.CNO,CNAME,FScore
from student,score,course
where student.SNO=score.SNO and score.CNO=course.CNO and CLNO='16CS1' and FScore<60

--ͳ�Ƹð༶������������
create view view_bujige2 as
select distinct SNO
from view_bujige

select count(*)as �˰༶�в���������
from view_bujige2

