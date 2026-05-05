class Logger
{
    private:
        static int fd;
        Logger();
    public:
        static int init(const char* path);
        static int log(const char* message);
        static void close();
};
