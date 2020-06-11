package coolJUnit;
import java.util.regex.Matcher; 
import java.util.regex.Pattern;

public class WordDealUtil {
	public static String wordFormat4DB(String name){
		if(name==null) {
			return null;
		}
		Pattern p = Pattern.compile("[A-Z]");
		Matcher m = p.matcher(name);
//		StringBuffer strBuffer = new StringBuffer();
		StringBuffer sb = new StringBuffer(); 
		while(m.find()){
			if(m.start()!=0) {
				m.appendReplacement(sb, ("_"+m.group()).toLowerCase()); 
			}
			//将当前匹配子串替换为指定字符串，
			//并且将替换后的子串以及其之前到上次匹配子串之后的字符串段添加 到一个StringBuffer对象里
		}   //将最后一次匹配工作后剩余的字符串添加到一个StringBuffer对象里
		return m.appendTail(sb).toString().toLowerCase(); 
	}
}

