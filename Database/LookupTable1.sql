--��ѯĳ�ſγ̵����гɼ��ķ����ƽ����
select CNO,AVG(FScore) as ƽ����,var(FScore) as ����
from score
group by CNO
having CNO='A1'


--��ѯĳ�ſγ�����ѡ��ѧ���ĵ÷����
select score.SNO as ѧ��,NAME as ����,FScore as �����ɼ�
from score,student
where score.SNO=student.SNO and CNO='A1'
order by(FScore)