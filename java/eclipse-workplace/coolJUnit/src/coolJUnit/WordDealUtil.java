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
			//����ǰƥ���Ӵ��滻Ϊָ���ַ�����
			//���ҽ��滻����Ӵ��Լ���֮ǰ���ϴ�ƥ���Ӵ�֮����ַ�������� ��һ��StringBuffer������
		}   //�����һ��ƥ�乤����ʣ����ַ�����ӵ�һ��StringBuffer������
		return m.appendTail(sb).toString().toLowerCase(); 
	}
}

