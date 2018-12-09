--create view ipgroup as
--select ip as ip,count(*) as c from answers where dateend is null group by ip;
--go

select count(*) from ipgroup inner join requests on ipgroup.ip=requests.ip where 
cnt>c and
ipgroup.ip not in (select ip from answers where dateend is not null);







