/*==============================================================*/
/* DBMS name:      Sybase SQL Anywhere 12                       */
/* Created on:     2018/6/25 21:08:08                           */
/*==============================================================*/


/*==============================================================*/
/* Table: academy                                               */
/*==============================================================*/
create table academy 
(
   ACNO                 integer                        not null,
   ACNAME               char(10)                       null,
   constraint PK_ACADEMY primary key (ACNO)
);

/*==============================================================*/
/* Index: academy_PK                                            */
/*==============================================================*/
create unique index academy_PK on academy (
ACNO ASC
);

/*==============================================================*/
/* Table: class                                                 */
/*==============================================================*/
create table class 
(
   CLNO                 char(10)                       not null,
   ACNO                 integer                        null,
   CLNAME               char(30)                       null,
   constraint PK_CLASS primary key (CLNO),
   foreign key(ACNO) references academy
);

/*==============================================================*/
/* Index: class_PK                                              */
/*==============================================================*/
create unique index class_PK on class (
CLNO ASC
);

/*==============================================================*/
/* Index: Relationship_5_FK                                     */
/*==============================================================*/
create index Relationship_5_FK on class (
ACNO ASC
);


/*==============================================================*/
/* Table: teacher                                               */
/*==============================================================*/
create table teacher 
(
   TNO                  char(10)                       not null,
   TNAME                char(10)                       null,
   AGE                  integer                        null,
   SEX                  char(10)                       null,
   POSITION             char(10)                        null,
   constraint PK_TEACHER primary key (TNO)
);



/*==============================================================*/
/* Index: teacher_PK                                            */
/*==============================================================*/
create unique index teacher_PK on teacher (
TNO ASC
);


/*==============================================================*/
/* Table: course                                                */
/*==============================================================*/
create table course 
(
   CNO                  char(10)                       not null,
   TNO                  char(10)                       null,
   CNAME                char(20)                       null,
   CREDIT               float                          null,
   CTIME                integer                        null,
   CTYPE                char(10)                       null,
   constraint PK_COURSE primary key (CNO),
   foreign key(TNO) references teacher
);

/*==============================================================*/
/* Index: course_PK                                             */
/*==============================================================*/
create unique index course_PK on course (
CNO ASC
);

/*==============================================================*/
/* Index: Relationship_3_FK                                     */
/*==============================================================*/
create index Relationship_3_FK on course (
TNO ASC
);

/*==============================================================*/
/* Table: score                                                 */
/*==============================================================*/
create table score 
(
   CNO                  char(10)                       null,
   SNO                  integer                        null,
   FScore               float                          null,
   SScore               float                          null,
   LScore               float                          null
);

/*==============================================================*/
/* Index: Relationship_1_FK                                     */
/*==============================================================*/
create index Relationship_1_FK on score (
SNO ASC
);

/*==============================================================*/
/* Index: Relationship_2_FK                                     */
/*==============================================================*/
create index Relationship_2_FK on score (
CNO ASC
);

/*==============================================================*/
/* Table: student                                               */
/*==============================================================*/
create table student 
(
   SNO                  integer                        not null,
   CLNO                 char(10)                       null,
   NAME                 char(10)                       not null,
   SEX                  char(10)                       null,
   AGE                  integer                        null,
   constraint PK_STUDENT primary key (SNO),
   foreign key(CLNO) references class
);

/*==============================================================*/
/* Index: student_PK                                            */
/*==============================================================*/
create unique index student_PK on student (
SNO ASC
);

/*==============================================================*/
/* Index: Relationship_4_FK                                     */
/*==============================================================*/
create index Relationship_4_FK on student (
CLNO ASC
);



