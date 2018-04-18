package schoolManager;

import java.util.*;
import java.sql.*;

public class ReviewManager{

    private Statement st = null;
    private ResultSet rs = null;

    public ReviewManager(DatabaseConnector dc){
	st = dc.getStatement();
    }

    public ArrayList<Review> getAllReviews() throws Exception{

	ArrayList<Review> list = new ArrayList<Review>();
	ResultSet rs = null;

	String sql = "select * from review_tbl order by star DESC";
	rs = st.executeQuery(sql);

	while(rs.next()){
	    int post_user_id = Integer.parseInt(rs.getString("post_user_id"));
	    String text = rs.getString("text");
	    String time = rs.getString("time");
	    int post_map_id = Integer.parseInt(rs.getString("post_map_id"));
	    int star = Integer.parseInt(rs.getString("star"));

	    Review review = new Review(post_user_id,text,time,post_map_id,star);
	    list.add(review);
	}

	return list;

    } 


    public Review getReviewById(String id) throws Exception{
	return getReviewById(Integer.parseInt(id));
    }

    public Review getReviewById(int id) throws Exception{
	
	Review review = null;
	ResultSet rs = null;

	String sql = "select * from schoolmap_tbl where id=" + id;
	rs = st.executeQuery(sql);

	if(!rs.next()){
	    return null;
	}

	review = new Review(Integer.parseInt(rs.getString("post_user_id")),rs.getString("text"),rs.getString("time"),
			  Integer.parseInt(rs.getString("post_map_id")),Integer.parseInt(rs.getString("star")));

	return review;
    }
    public void addReview(Review rv) throws Exception{
	String sql = "insert into review_tbl(post_user_id,text,time,post_map_id,star) values('"+rv.getPost_user_id() +"' , '"+rv.getText() + "' , '"+rv.getTime() + "' , '"+rv.getPost_map_id() + "' , '"+rv.getStar() + "')";
    
	st.executeUpdate(sql);

    }


    
}