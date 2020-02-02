using Botworx.Runtime;
public class weight : Fact<float>
{
}
public class Foo : Expert
{
    public void foo(Space space, Fact arg)
    {
        IFact x = arg.Subject;
        {
            foreach(Entity y in space.MatchSubjPred<Entity>(x, Test.ent_has))
            {
                if(space.Exists(y, Test.ent_is, Test.ent_bar))
                {
                    space.Post(new Fact<Entity>(FactKind.AddBelief, y, Test.ent_is, Test.ent_foo));
                }
            }
        }
    }
    public static void fooStub(Expert expert, Space space, Fact arg)
    {
        ((Foo)expert).foo(space, arg);
    }
    public void bar(Space space, Fact arg)
    {
        IFact x = arg.Subject;
        {
            foreach(float y in space.MatchSubjPred<float>(x, Test.ent_weight))
            {
                if(space.Exists(y, Test.ent_is, Test.ent_bar))
                {
                    space.Post(new Fact<Entity>(FactKind.AddBelief, y, Test.ent_is, Test.ent_foo));
                }
            }
        }
    }
    public static void barStub(Expert expert, Space space, Fact arg)
    {
        ((Foo)expert).bar(space, arg);
    }
}
public class Test : Module
{
    static Entity ent_weight = EntityManager.Instance().Intern("weight");
    static Entity ent_has = EntityManager.Instance().Intern("has");
    static Entity ent_is = EntityManager.Instance().Intern("is");
    static Entity ent_bar = EntityManager.Instance().Intern("bar");
    static Entity ent_foo = EntityManager.Instance().Intern("foo");
}
