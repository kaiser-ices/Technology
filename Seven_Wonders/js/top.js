
function change_tab(vew_tab) {
// 全部消す
document.getElementById('tab1').style.display = 'none';
document.getElementById('tab2').style.display = 'none';
document.getElementById('tab3').style.display = 'none';
//指定したタブを表示
document.getElementById(vew_tab).style.display = 'block';
}
