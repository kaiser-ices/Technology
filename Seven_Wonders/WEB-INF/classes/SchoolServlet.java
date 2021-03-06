import java.io.*;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import schoolManager.*;
import java.text.SimpleDateFormat;
import java.util.Date;

public class SchoolServlet extends HttpServlet {
    private static String DB_NAME       = "school_db";               // DB名
    private static String DB_USER       = "root";                  // DBのユーザ名
    private static String DB_PASS       = "root";                  // DBのパスワード 
    private int uid = 0;

    // ログインのビューを担当
    private static String LOGIN_JSP     = "/WEB-INF/Login.jsp";
    private static String TOP_JSP = "/WEB-INF/Top.jsp";

    /**
     * サーブレットがPOSTメソッドでアクセスされた際に呼ばれる．
     */
    public void doPost(HttpServletRequest req, HttpServletResponse res)
	throws ServletException, IOException{

	// doProcessを呼ぶことでGET/POSTのどちらでアクセスされても同じ処理を実行
	doProcess(req, res);
    }

    /**
     * サーブレットがGETメソッドでアクセスされた際に呼ばれる．
     */
    public void doGet(HttpServletRequest req, HttpServletResponse res)
	throws ServletException, IOException {

	// doProcessを呼ぶことでGET/POSTのどちらでアクセスされても同じ処理を実行
	doProcess(req, res);
    }
 /**
     * クライアントから要求された処理をactionから判別し実行する
     */
    protected void doProcess(HttpServletRequest req, HttpServletResponse res)
	throws ServletException, IOException {

	String nextView = ""; // 処理結果の表示を委託するJSPのパス
	DatabaseConnector dc = null; // データベースへの接続を行うオブジェクト
	UserManager um = null; // ユーザ認証や登録に関する処理を担当
	RoomManager rm = null;
        ReviewManager rv = null;

	try {
	    dc = new DatabaseConnector(DB_NAME, DB_USER, DB_PASS);
	    dc.openConnection(); // DBへ接続
	    
	    um = new UserManager(dc);
	    rm = new RoomManager(dc);
            rv = new ReviewManager(dc);

	    // 前のページから渡される値を「UTF-8」に設定
	    req.setCharacterEncoding("UTF-8");
	    // これから表示するページのMIMEを設定
	    res.setContentType("text/html;charset=UTF-8");


	    /*
	     * ユーザからの要求はURLの後方に付加された「？」
	     * 以降にGETメソッドのactionパラメータとして付加される
	     */
	    String action = req.getParameter("action");
	    if (action == null) {
		action = "";
	    }

	    /**
	     * 以下のif文でユーザからの要求を判別し，適切処理を行う
	     */
	    if (action.equals("") || action.equals("loginPage")) {
		nextView = LOGIN_JSP; // ログイン用のページを表示
	    } else if (action.equals("login")) {

		// 認証の処理を実行
		if (login(um, req)) {
		    nextView = showRooms(rm , req); // ログイン成功
		    nextView = showReviews(rv , req);
		} else {
		    nextView = LOGIN_JSP; // ログイン失敗
		}

	    } else if (action.equals("logout")) {

		// ログアウトの処理を実行
		nextView = logout(req);

	    } else if (action.equals("registration")) {

		// 新規ユーザの登録処理を実行
		nextView = registration(um, req);

	    } else if (action.equals("rev")){
		nextView = addReviews(rv,req);
		ArrayList<Review> list = rv.getAllReviews();

		req.setAttribute("reviewList" , list);
		ArrayList<Room> lists = rm.getAllRooms();

		req.setAttribute("roomList" , lists);


	    }

	    if (nextView.equals("")) {
		// actionパラメータの指定が無い，または不明な処理が要求された場合
		req.setAttribute("message", "不正なアクションが要求されました("
				 + req.getParameter("action") + ")");

		nextView = LOGIN_JSP;
	    }

	    dc.closeConnection(); // データベースへの接続を切断

	} catch (Exception e) {
	    // 例外の詳細を/usr/tomcat/logs/catalina.outへ出力
	    // 問題が発生した際に参考にすると良い
	    e.printStackTrace();
	    req.setAttribute("message", "例外が発生しました:" + e.toString());
	    nextView = LOGIN_JSP;
	} finally {
	    /*
	     * 正常に処理された場合も，エラーの場合もビューとして指定されたJSP
	     * へフォワードし，クライアントに結果を返す
	     */
	    req.getRequestDispatcher(nextView).forward(req, res);
	}
    }
/**
     * ユーザが入力したユーザ名とパスワードを検証し，ログインの処理を行う
     */
    private boolean login(UserManager um, HttpServletRequest req)
	throws Exception {
	String userName = req.getParameter("uname"); // ユーザ名
	String password = req.getParameter("pass");// パスワード

	if (!isValid(userName) || !isValid(password)) {
	    req.setAttribute("message", "記入漏れがあります");
	    return false;
	} else if (um.authenticate(userName, password) == false) {
	    req.setAttribute("message", "ユーザ名またはパスワードが違います");
	    return false;
	} else {
	    // ログインに成功した場合
	    HttpSession session = req.getSession(true);
	    session.setAttribute("userName",userName);
	    req.setAttribute("message", "認証に成功しました");
	    uid = um.getId(userName,password);
	}

	return true;
    }
/**
     * 新規ユーザの登録処理を行う
     */
    private String registration(UserManager um, HttpServletRequest req)
	throws Exception {
	String userName = req.getParameter("uname"); // ユーザ名
	String password = req.getParameter("pass"); // パスワード
	String password2 = req.getParameter("pass2"); // パスワード（確認）

	if (!isValid(userName) || !isValid(password) || !isValid(password2)) {
	    req.setAttribute("message", "記入漏れがあります");
	} else if (!password.equals(password2)) {
	    req.setAttribute("message", "パスワードが確認用と一致しません");
	} else if (um.registration(userName, password)) {
	    req.setAttribute("message", "登録に成功しました");
	} else {
	    req.setAttribute("message", "すでに登録されています");
	}

	return LOGIN_JSP;
    }

    /**
     * セッションを無効化し，ログアウトの処理を行う
     */
    private String logout(HttpServletRequest req) {

	HttpSession session = req.getSession(false); // セッションを取得
	if (session != null) {
	    // セッションの無効化
	    session.invalidate (); //(D)
	    req.setAttribute("message","ログアウトしました");
	}

	// ログイン画面へ移動させる
	return LOGIN_JSP;
    }

    private String showRooms(RoomManager rm , HttpServletRequest req)
	throws Exception {

	ArrayList<Room> list = rm.getAllRooms();

	req.setAttribute("roomList" , list);

	return TOP_JSP;

	    }

    private String showReviews(ReviewManager rv , HttpServletRequest req)
	throws Exception {

	ArrayList<Review> list = rv.getAllReviews();

	req.setAttribute("reviewList" , list);

	return TOP_JSP;

	    }

    protected boolean isValid(String str) {

	if (str != null && !str.equals("")) {
	    return true;
	} else {
	    return false;
	}
    }

    private String addReviews(ReviewManager rv , HttpServletRequest req)
	throws Exception {
	
	String build1 = req.getParameter("build");
	int build2 = Integer.parseInt(build1);
	String hoshi1 = req.getParameter("hoshi");
	int hoshi2 = Integer.parseInt(hoshi1);
	String msg = req.getParameter("msg");
	Date d = new Date();
        SimpleDateFormat d1 = new SimpleDateFormat("yyyy年MM月dd日 HH時mm分ss秒");
	String d2 = d1.format(d);
	Review rev = new Review(uid,msg,d2,build2,hoshi2);
	rv.addReview(rev);
	
	return TOP_JSP;

    }
	
}