package schoolManager;

public class User{

    private int id = 0;
    private String password = "";
    private int fail = 0;

    public User(int id, String password, int fail){

	this.id = id;
	this.password = password;
	this.fail = fail;

    }

    public int getId(){

	return id;

    }

    public String getPassword(){

	return password;

    }

    public int getFail(){

	return fail;

    }
}
