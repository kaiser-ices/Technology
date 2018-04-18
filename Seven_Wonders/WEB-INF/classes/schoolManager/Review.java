package schoolManager;

public class Review{

    private int post_user_id = 0;
    private String text = "";
    private String time = "";
    private int post_map_id = 0;
    private int star = 0;

    public Review(int post_user_id,String text,String time,int post_map_id,int star){

	this.post_user_id = post_user_id;
	this.text = text;
	this.time = time;
	this.post_map_id = post_map_id;
	this.star = star;
    }

    public int getPost_user_id(){

	return post_user_id;

    }

    public String getText(){

	return text;

    }

    public String getTime(){

	return time;

    }

    public int getPost_map_id(){

        return post_map_id;

    }

    public int getStar(){

	return star;

    }
}
