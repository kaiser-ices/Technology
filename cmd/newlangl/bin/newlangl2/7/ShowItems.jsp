<%@ page contentType="text/html;charset=UTF-8"%>
<jsp:useBean id="message" class="java.lang.String" scope="request"/>
<jsp:useBean id="userName" class="java.lang.String" scope="session"/>
<jsp:useBean id="itemList" type="java.util.ArrayList<webshop.Item>" scope="request"/>

<html>
  <head>
    <title>商品一覧</title>
  </head>
  <body>
    <div style="width: 500; margin: 0 auto;">

      <% if(message != null){ %>
        <font color="red"><%=message %></font>
        <br>
        <% } %>

        <di align=right>
          ようこそ、<%=userName %>さん
          <a href="?action=logout">（ログアウト）</a>
        </div>

        <h1>商品紹介</h1>
        <hr>
          <table border=1>
            <tr>
              <td>商品ID</td>
              <td>商品名</td>
              <td>価格</td>
              <td>カートへ追加</td>
            </tr>

            <% for(int i =0; i<itemList.size();i++){  %>
              <tr>
                <td><%= itemList.get(i).getid() %></td>
                <td><%= itemList.get(i).getPrice() %>円</td>
                <td>
                  <a href="?action=add&id=<%= itemList.get(i).getid() %>">追加</a>
                </td>
              </tr>
            <% } %>

          </table>
          <a href="?action=showCart">カートの中を表示</a>

        </div>
      </body>
    </html>
