/*==============================================================*/
/* DBMS name:      Microsoft SQL Server 2012                    */
/* Created on:     2018/7/4 15:36:57                            */
/*==============================================================*/


if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('class') and o.name = 'FK_CLASS_RELATIONS_ACADEMY')
alter table class
   drop constraint FK_CLASS_RELATIONS_ACADEMY
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('course') and o.name = 'FK_COURSE_RELATIONS_TEACHER')
alter table course
   drop constraint FK_COURSE_RELATIONS_TEACHER
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('score') and o.name = 'FK_SCORE_RELATIONS_STUDENT')
alter table score
   drop constraint FK_SCORE_RELATIONS_STUDENT
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('score') and o.name = 'FK_SCORE_RELATIONS_COURSE')
alter table score
   drop constraint FK_SCORE_RELATIONS_COURSE
go

if exists (select 1
   from sys.sysreferences r join sys.sysobjects o on (o.id = r.constid and o.type = 'F')
   where r.fkeyid = object_id('student') and o.name = 'FK_STUDENT_RELATIONS_CLASS')
alter table student
   drop constraint FK_STUDENT_RELATIONS_CLASS
go

if exists (select 1
            from  sysobjects
           where  id = object_id('academy')
            and   type = 'U')
   drop table academy
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('class')
            and   name  = 'Relationship_5_FK'
            and   indid > 0
            and   indid < 255)
   drop index class.Relationship_5_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('class')
            and   type = 'U')
   drop table class
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('course')
            and   name  = 'Relationship_3_FK'
            and   indid > 0
            and   indid < 255)
   drop index course.Relationship_3_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('course')
            and   type = 'U')
   drop table course
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('score')
            and   name  = 'Relationship_2_FK'
            and   indid > 0
            and   indid < 255)
   drop index score.Relationship_2_FK
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('score')
            and   name  = 'Relationship_1_FK'
            and   indid > 0
            and   indid < 255)
   drop index score.Relationship_1_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('score')
            and   type = 'U')
   drop table score
go

if exists (select 1
            from  sysindexes
           where  id    = object_id('student')
            and   name  = 'Relationship_4_FK'
            and   indid > 0
            and   indid < 255)
   drop index student.Relationship_4_FK
go

if exists (select 1
            from  sysobjects
           where  id = object_id('student')
            and   type = 'U')
   drop table student
go

if exists (select 1
            from  sysobjects
           where  id = object_id('teacher')
            and   type = 'U')
   drop table teacher
go

/*==============================================================*/
/* Table: academy                                               */
/*==============================================================*/
create table academy (
   ACNO                 int                  not null,
   ACNAME               char(10)             null,
   constraint PK_ACADEMY primary key nonclustered (ACNO)
)
go

/*==============================================================*/
/* Table: class                                                 */
/*==============================================================*/
create table class (
   CLNO                 char(10)             not null,
   ACNO                 int                  null,
   CLNAME               char(30)             null,
   constraint PK_CLASS primary key nonclustered (CLNO)
)
go

/*==============================================================*/
/* Index: Relationship_5_FK                                     */
/*==============================================================*/
create index Relationship_5_FK on class (
ACNO ASC
)
go

/*==============================================================*/
/* Table: course                                                */
/*==============================================================*/
create table course (
   CNO                  char(10)             not null,
   TNO                  char(10)             null,
   CNAME                char(20)             null,
   CREDIT               float                null,
   CTIME                int                  null,
   CTYPE                char(10)             null,
   constraint PK_COURSE primary key nonclustered (CNO)
)
go

/*==============================================================*/
/* Index: Relationship_3_FK                                     */
/*==============================================================*/
create index Relationship_3_FK on course (
TNO ASC
)
go

/*==============================================================*/
/* Table: score                                                 */
/*==============================================================*/
create table score (
   SNO                  int                  null,
   CNO                  char(10)             null,
   FScore               float                null,
   SScore               float                null,
   LScore               float                null
)
go

/*==============================================================*/
/* Index: Relationship_1_FK                                     */
/*==============================================================*/
create index Relationship_1_FK on score (
SNO ASC
)
go

/*==============================================================*/
/* Index: Relationship_2_FK                                     */
/*==============================================================*/
create index Relationship_2_FK on score (
CNO ASC
)
go

/*==============================================================*/
/* Table: student                                               */
/*==============================================================*/
create table student (
   SNO                  int                  not null,
   CLNO                 char(10)             null,
   NAME                 char(10)             not null,
   SEX                  char(10)             null,
   AGE                  int                  null,
   constraint PK_STUDENT primary key nonclustered (SNO)
)
go

/*==============================================================*/
/* Index: Relationship_4_FK                                     */
/*==============================================================*/
create index Relationship_4_FK on student (
CLNO ASC
)
go

/*==============================================================*/
/* Table: teacher                                               */
/*==============================================================*/
create table teacher (
   TNO                  char(10)             not null,
   TNAME                char(10)             null,
   AGE                  int                  null,
   SEX                  char(10)             null,
   POSITION             char(10)             null,
   constraint PK_TEACHER primary key nonclustered (TNO)
)
go

alter table class
   add constraint FK_CLASS_RELATIONS_ACADEMY foreign key (ACNO)
      references academy (ACNO)
go

alter table course
   add constraint FK_COURSE_RELATIONS_TEACHER foreign key (TNO)
      references teacher (TNO)
go

alter table score
   add constraint FK_SCORE_RELATIONS_STUDENT foreign key (SNO)
      references student (SNO)
go

alter table score
   add constraint FK_SCORE_RELATIONS_COURSE foreign key (CNO)
      references course (CNO)
go

alter table student
   add constraint FK_STUDENT_RELATIONS_CLASS foreign key (CLNO)
      references class (CLNO)
go

