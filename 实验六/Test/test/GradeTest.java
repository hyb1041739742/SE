import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Test;

import static org.junit.Assert.*;

public class GradeTest {
    Grade grade;

    @BeforeClass
    public static void setUpBeforeClass() throws Exception{
        System.out.println("测试开始了");
    }
    @AfterClass
    public static void tearDownAfterClass() throws Exception{
        System.out.println("测试结束了");
    }


    @org.junit.Before
    public void setUp() throws Exception {
        System.out.println("grade被创建了");
        grade = new Grade();
    }

    @org.junit.After
    public void tearDown() throws Exception {
        System.out.println("grade被销毁了");
        grade=null;
    }
    @Test
    public void testGrade(){
        for (int i = 0; i <= 2050; i+=50) {
            int level = grade.judgeGrade(i);
            System.out.println("风险"+i+"的评估等级是"+level);

        }

    }
}