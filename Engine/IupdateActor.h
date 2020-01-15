class IupdateActor
{
private:
public:
	IupdateActor(void);
	virtual ~IupdateActor(void);

	virtual void load();
	virtual void update();
	virtual void destroy();
};