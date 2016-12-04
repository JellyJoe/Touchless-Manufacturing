class Arm : public QObject
{
    Q_OBJECT

private:
    char outgoingData[256];
    char incomingData[256];
    int dataLength;
    int cycle;

public:

    Serial* ArmSp;
    explicit Arm(QObject *parent = 0);

public slots:
    void demoClicked();
    void manualLuanched();
    void saveWithPump();
    void saveWithoutPump();
    void executeManualMovement();
    void setPositionA();
    void setPositionB();
    void setPositionC();
    void setHeight();
    void executeAutoMovement();
    void stopMovement();
};
