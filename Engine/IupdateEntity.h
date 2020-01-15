class IupdateEntity
{
private:
public:
	IupdateEntity(void);
	virtual ~IupdateEntity(void);

	virtual void load();
	virtual void update();
	virtual void destroy();
};