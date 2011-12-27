
DESCRIPTION
-----------
Tencent QQ, generally referred to as QQ, is the most popular 
free instant messaging computer program in mainland China. 
As of July 11, 2011, the active QQ users accounts for QQ 
IM totaled 812.3 million,possibly making it the world's 
second largest online community. The number of simultaneous 
online QQ accounts exceeded 100 million. In February 2011, 
QQ.com ranked 10th overall in the Alexa Internet rankings 
just behind Twitter ranked 9th.

OAuth (Open Authorization) is an open standard for 
authorization.OAuth allows users to hand out tokens 
instead of credentials to their data hosted by a given 
service provider. Each token grants access to a specific 
site or specific resources and for a defined duration. 
This allows a user to grant a third party site access 
to their information stored with another service provider, 
without sharing their access permissions or the full extent 
of their data.

The QQ module based on OAuth protocol with QQ Login 
application. It allows qq acount to log in drupal.
You can apply the QQ Login application for your site 
by http://connect.qq.com/intro/login. View more api document,
please click Tencent Open Platform.Now,the QQ module for 
drupal7. Besides drupal 6 version is ok, but it is not commited 
in drupal.org until the drupal7 one is published.

Apply THE QQ LOGIN APPLICATION STEPS:
-------------------------------------

    1.Open http://connect.qq.com/intro/login
    2.Verify your site,copy certain code in you web page head tag
    part. eg.my site code <meta property="qc:admins" 
    content="1543255227642501453526727" />
    3.Edit basic information of your application,incude site name,
    url,description,logo,login page,callback page...
    4.Take APP ID and KEY of your application
    5.Apply for online your application
    6.Passed your apllication.END

ADMINISTER CONFIGRATION
-----------------------
Path: http://your-drupal-site-url/admin/config/people/qq
Value:
    1.oauth consumer key : Please input APP ID of your application
    2.oauth consumer secret : Please input KEY of your application
    3.oauth callback : Please input CALLBACK of your application

Module Demo: drupaluser.org
Author: Hejinlong , Drupal Beijing meetup organizer 
        & Drupaluser.org founder , jinlonghe@yahoo.cn
