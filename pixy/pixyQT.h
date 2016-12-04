class Pixy : public QOject
{
    Q_OBJECT
private:
    char incomingData[2];
	char outgoingData[2];
    int dataLength;
public:
    Serial * pixySP;
    explicit Pixy(QObject * parent = 0);
public slots:
    void getBlocks();//Execute pixy to retrieve detected blocks
    bool checkBlocks();//To check for receive blocks is true
};
