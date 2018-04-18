package schoolManager;

import java.util.*;
import java.sql.*;
import java.security.*;
import java.math.BigInteger;

public class UserManager {

    private Statement st = null;
    private ResultSet rs = null;

    public UserManager(DatabaseConnector dc) {
	st = dc.getStatement();
    }

    public boolean authenticate(String username, String password)
	throws Exception {
	boolean ret = false;
	String sql = "select * from user_tbl where username = '" + username +"'"; //(A)
	rs = st.executeQuery(sql);

	if (!rs.next()) {
	    return false;
	}

	int failCount = rs.getInt("fail");
	String dbpass = rs.getString("password");
	String md5pass = md5(password);

	if (dbpass.equals(md5pass) && failCount <= 3) {
	    failCount = 0;
	    ret = true;
	} else {
	    failCount++;
	    ret = false;
	}

	sql = "update user_tbl set fail = " + failCount + " where username = '" + username + "'"; //(B)
	st.executeUpdate(sql);

	return ret;
    }

    public boolean registration(String username, String password)
	throws Exception {

	String sql = "select password from user_tbl where username = '" + username + "'";
	rs = st.executeQuery(sql);

	if (rs.next()) {
	    return false;
	}
	rs.close();

	String md5pass = md5(password);
	sql = "insert into user_tbl (username,password,fail) values ('" + username + "','" + md5pass + "' , 0)";

	st.executeUpdate(sql);

	return true;

    }

    private static String md5(String password) throws NoSuchAlgorithmException {
	MessageDigest md5 = MessageDigest.getInstance("MD5");
	md5.update(password.getBytes());
	String digest = new BigInteger(1, md5.digest()).toString(16);
	char[] buf = new char[32];
	Arrays.fill(buf, '0');
	System.arraycopy(digest.toCharArray() , 0, buf, buf.length - digest.length(), digest.length());
	return new String(buf);
    }

    public int getId(String username,String password)throws Exception{
	String sql = "select * from user_tbl where username = '" + username +"'"; //(A)
	rs = st.executeQuery(sql);

	if (!rs.next()) {
           
	}
	String dbpass = rs.getString("password");
	String md5pass = md5(password);
	if (dbpass.equals(md5pass)){
	    return rs.getInt("id");
	}else{
	    return -1;
	}
    }
}
