# Wordpress

1. Create the database datadir with `mysql_install_db`:

   ```bash
   $ mysql
   mysql> CREATE DATABASE wordpress_dtec;
   Query OK, 1 row affected (0.47 sec)
   ```

2. Set permissions/privileges for the Wordpress user:

   ```bash
   # Allow the dtec user to connect remotely to this MySQL server
   mysql> GRANT USAGE ON *.* TO 'dtec'@'%' IDENTIFIED BY PASSWORD '<pass>'

   # Allow dtec user to connect 1) from any host and modify
   # everything in the the wordpress_dtec database.
   mysql> GRANT ALL PRIVILEGES ON `wordpress_dtec`.* TO 'dtec'@'%';
   mysql> show grants for 'dtec'@'%';
   +-----------------------------------------------------------------------------------------------------+
   | Grants for dtec@%                                                                                   |
   +-----------------------------------------------------------------------------------------------------+
   | GRANT USAGE ON *.* TO 'dtec'@'%' IDENTIFIED BY PASSWORD '*196BDEDE2AE4F84CA44C47D54D78478C7E2BD7B7' | 
   | GRANT ALL PRIVILEGES ON `wordpress_dtec`.* TO 'dtec'@'%'                                            | 
   +-----------------------------------------------------------------------------------------------------+
   2 rows in set (0.00 sec)
   ```
