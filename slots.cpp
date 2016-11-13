class Arm : public QObject
{
    Q_OBJECT

private:
    char outgoingData[256];
    int dataLength;

public:

    Serial* ArmSp;
    explicit Arm(QObject *parent = 0);

public slots:
    void demoClicked();
    void manualLuanched();
    void saveWithPump();
    void saveWithoutPump();
    void executeManualMovement();
    void stopMovement();
};
