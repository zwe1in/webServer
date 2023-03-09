#ifndef TASK_H
#define TASK_H

class Task{
public:
    Task() : func(nullptr){}
    Task(Task &) = delete;
    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;
    Task(Task&& other)
    {
        func = other.func;
        other.func = nullptr;
    }
    Task& operator=(Task&& other)
    {
        if(&other != this)
        {
            delete func;
            func = other.func;
            other.func = nullptr;
        }
        return *this;
    }

    template<typename F>
    Task(F&& f) : func(new Exec<F>(std::forward<F>(f))){}

    template<typename F>
    void reset(F&& f)
    {
        delete func;
        func = new Exec<F>(std::forward<F>(f));
    }
    bool isSet() const { return func != nullptr; }
    void operator()(){ func->callback(); }
private:
    struct ExecBase{
        virtual void callback() = 0;
        virtual ~ExecBase() = default;
    };

    template<typename F>
    struct Exec : ExecBase{
        F foo;
        Exec(F&& f) : foo(std::forward<F>(f)){}
        ~Exec() = default;
        void callback(){ foo(); }
    };

private:
    ExecBase *func;
};

#endif