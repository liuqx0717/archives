--update answers set datestart=dateadd(d,-1,datestart), dateend=dateadd(d,-1,dateend) where token=773648194 or token=961452264;

select * from requests where cnt>10;
select * from answers where dateend is not null /*and DATEDIFF(mi,dateend,SYSDATETIME())<30*/ order by dateend ;
--select * from answers where  DATEDIFF(mi,datestart,SYSDATETIME())<30 order by datestart ;
--select count(*) from answers;
