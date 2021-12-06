public class Client {
    public static void main(String[] args) {
        GoldCard goldCard = new GoldCard();
        SilverCard silverCard = new SilverCard();
        Tenant tenant = new Tenant();
        tenant.display();
        goldCard.display();
        silverCard.display();
    }
}
