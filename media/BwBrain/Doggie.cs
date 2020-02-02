namespace DoggieNamespace{
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Text;
    using System.IO;
    public class Doggie : Expert
    {
        public IEnumerable<TaskStatus> Main(Method method, Space space, Note note)
        {
            Task bwx_task, bwx_task_0, bwx_task_1, bwx_task_2;
            Fact bwx_fact;
            bwx_task = method;
            do{
                bwx_task_0 = bwx_task;
                bwx_task = new PrioritySelect(bwx_task);
                bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_bodily));
                space.Post(new Note(bwx_fact, bwx_task));
                bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_active));
                space.Post(new Note(bwx_fact, bwx_task));
                bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_passive));
                space.Post(new Note(bwx_fact, bwx_task));
            }while(false);
            bwx_task = bwx_task_0;
            yield return TaskStatus.Success;
        }
        public static void MainStub(Expert expert, Space space, Fact arg)
        {
            Method method = new Method(note.Author);
            method.Enumerable = ((Doggie)expert).Main(method, space, note);
            method.Schedule();
        }
        public IEnumerable<TaskStatus> Bodily(Method method, Space space, Note note)
        {
            Task bwx_task, bwx_task_0, bwx_task_1, bwx_task_2;
            Fact bwx_fact;
            bwx_task = method;
            do{
                bwx_task_0 = bwx_task;
                bwx_task = new ProbabilitySelect(bwx_task);
                if(bwx_weight < 0.6666667)
                {
                    do{
                        bwx_task_1 = bwx_task;
                        bwx_task = new Case(bwx_task);
                        bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, fail));
                        space.Post(new Note(bwx_fact, bwx_task));
                    }while(false);
                    bwx_task = bwx_task_1;
                }
                else if(bwx_weight < 0.7333333)
                {
                    do{
                        bwx_task_1 = bwx_task;
                        bwx_task = new Case(bwx_task);
                        bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_animate));
                        bwx_fact.AddFact(new Fact<Entity>(name, "LayingIdle"));
                        bwx_fact.AddFact(new Fact<Entity>(speed, .2));
                        bwx_fact.AddFact(new Fact<Entity>(loop, TestModule.ent_false));
                        space.Post(new Note(bwx_fact, bwx_task));
                        bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_animate));
                        bwx_fact.AddFact(new Fact<Entity>(name, "Sleeping"));
                        bwx_fact.AddFact(new Fact<Entity>(speed, .2));
                        bwx_fact.AddFact(new Fact<Entity>(loop, TestModule.ent_false));
                        space.Post(new Note(bwx_fact, bwx_task));
                    }while(false);
                    bwx_task = bwx_task_1;
                }
                else if(bwx_weight < 0.8666667)
                {
                    do{
                        bwx_task_1 = bwx_task;
                        bwx_task = new Case(bwx_task);
                        bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_random_turn));
                        bwx_fact.AddFact(new Fact<Entity>(time, 1.5));
                        space.Post(new Note(bwx_fact, bwx_task));
                        bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_random_move));
                        bwx_fact.AddFact(new Fact<Entity>(name, "StalkingPrey"));
                        bwx_fact.AddFact(new Fact<Entity>(speed, 8.0));
                        bwx_fact.AddFact(new Fact<Entity>(time, 0.5));
                        space.Post(new Note(bwx_fact, bwx_task));
                        bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_animate));
                        bwx_fact.AddFact(new Fact<Entity>(name, "Peeing"));
                        bwx_fact.AddFact(new Fact<Entity>(speed, 1.0));
                        bwx_fact.AddFact(new Fact<Entity>(loop, TestModule.ent_false));
                        space.Post(new Note(bwx_fact, bwx_task));
                        bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_random_turn));
                        bwx_fact.AddFact(new Fact<Entity>(time, 1.5));
                        space.Post(new Note(bwx_fact, bwx_task));
                        bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_random_move));
                        bwx_fact.AddFact(new Fact<Entity>(name, "JumpyRun"));
                        bwx_fact.AddFact(new Fact<Entity>(speed, 2.0));
                        bwx_fact.AddFact(new Fact<Entity>(time, 6.0));
                        space.Post(new Note(bwx_fact, bwx_task));
                    }while(false);
                    bwx_task = bwx_task_1;
                }
                else if(bwx_weight < 1)
                {
                    do{
                        bwx_task_1 = bwx_task;
                        bwx_task = new Case(bwx_task);
                        bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_animate));
                        bwx_fact.AddFact(new Fact<Entity>(name, "ScratchingBack"));
                        bwx_fact.AddFact(new Fact<Entity>(speed, 1.0));
                        bwx_fact.AddFact(new Fact<Entity>(loop, TestModule.ent_false));
                        space.Post(new Note(bwx_fact, bwx_task));
                        bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_animate));
                        bwx_fact.AddFact(new Fact<Entity>(name, "Scratching"));
                        bwx_fact.AddFact(new Fact<Entity>(speed, 1.0));
                        bwx_fact.AddFact(new Fact<Entity>(loop, TestModule.ent_false));
                        space.Post(new Note(bwx_fact, bwx_task));
                    }while(false);
                    bwx_task = bwx_task_1;
                }
            }while(false);
            bwx_task = bwx_task_0;
            yield return TaskStatus.Success;
        }
        public static void BodilyStub(Expert expert, Space space, Fact arg)
        {
            Method method = new Method(note.Author);
            method.Enumerable = ((Doggie)expert).Bodily(method, space, note);
            method.Schedule();
        }
        public IEnumerable<TaskStatus> Active(Method method, Space space, Note note)
        {
            Task bwx_task, bwx_task_0, bwx_task_1, bwx_task_2;
            Fact bwx_fact;
            bwx_task = method;
            do{
                bwx_task_0 = bwx_task;
                bwx_task = new ProbabilitySelect(bwx_task);
                if(bwx_weight < 0.16)
                {
                    do{
                        bwx_task_1 = bwx_task;
                        bwx_task = new Case(bwx_task);
                        bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, fail));
                        space.Post(new Note(bwx_fact, bwx_task));
                    }while(false);
                    bwx_task = bwx_task_1;
                }
                else if(bwx_weight < 0.2)
                {
                    do{
                        bwx_task_1 = bwx_task;
                        bwx_task = new Case(bwx_task);
                        bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_animate));
                        bwx_fact.AddFact(new Fact<Entity>(name, "ChaseTail"));
                        bwx_fact.AddFact(new Fact<Entity>(speed, 1.0));
                        bwx_fact.AddFact(new Fact<Entity>(loop, TestModule.ent_true));
                        space.Post(new Note(bwx_fact, bwx_task));
                    }while(false);
                    bwx_task = bwx_task_1;
                }
                else if(bwx_weight < 1)
                {
                    do{
                        bwx_task_1 = bwx_task;
                        bwx_task = new Case(bwx_task);
                        bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_random_turn));
                        bwx_fact.AddFact(new Fact<Entity>(degree, 1.0));
                        space.Post(new Note(bwx_fact, bwx_task));
                        bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_random_move));
                        bwx_fact.AddFact(new Fact<Entity>(speed, 4.0));
                        space.Post(new Note(bwx_fact, bwx_task));
                    }while(false);
                    bwx_task = bwx_task_1;
                }
            }while(false);
            bwx_task = bwx_task_0;
            yield return TaskStatus.Success;
        }
        public static void ActiveStub(Expert expert, Space space, Fact arg)
        {
            Method method = new Method(note.Author);
            method.Enumerable = ((Doggie)expert).Active(method, space, note);
            method.Schedule();
        }
        public IEnumerable<TaskStatus> Passive(Method method, Space space, Note note)
        {
            Task bwx_task, bwx_task_0, bwx_task_1, bwx_task_2;
            Fact bwx_fact;
            bwx_task = method;
            do{
                bwx_task_0 = bwx_task;
                bwx_task = new ProbabilitySelect(bwx_task);
                if(bwx_weight < 0.5)
                {
                    do{
                        bwx_task_1 = bwx_task;
                        bwx_task = new Case(bwx_task);
                        bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_animate));
                        bwx_fact.AddFact(new Fact<Entity>(name, "Sitting"));
                        bwx_fact.AddFact(new Fact<Entity>(speed, .34));
                        bwx_fact.AddFact(new Fact<Entity>(loop, TestModule.ent_false));
                        space.Post(new Note(bwx_fact, bwx_task));
                    }while(false);
                    bwx_task = bwx_task_1;
                }
                else if(bwx_weight < 1)
                {
                    do{
                        bwx_task_1 = bwx_task;
                        bwx_task = new Case(bwx_task);
                        bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_animate));
                        bwx_fact.AddFact(new Fact<Entity>(name, "LayingIdle"));
                        bwx_fact.AddFact(new Fact<Entity>(speed, .67));
                        bwx_fact.AddFact(new Fact<Entity>(loop, TestModule.ent_false));
                        space.Post(new Note(bwx_fact, bwx_task));
                    }while(false);
                    bwx_task = bwx_task_1;
                }
            }while(false);
            bwx_task = bwx_task_0;
            yield return TaskStatus.Success;
        }
        public static void PassiveStub(Expert expert, Space space, Fact arg)
        {
            Method method = new Method(note.Author);
            method.Enumerable = ((Doggie)expert).Passive(method, space, note);
            method.Schedule();
        }
        public IEnumerable<TaskStatus> RandomMove(Method method, Space space, Note note)
        {
            Task bwx_task, bwx_task_0, bwx_task_1, bwx_task_2;
            Fact bwx_fact;
            bwx_task = method;
            do{
                bwx_task_0 = bwx_task;
                bwx_task = new Parallel(bwx_task);
                bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_translate));
                bwx_fact.AddFact(new Fact<Entity>(speed, s));
                bwx_fact.AddFact(new Fact<Entity>(time, t));
                space.Post(new Note(bwx_fact, bwx_task));
                bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_animate));
                bwx_fact.AddFact(new Fact<Entity>(name, n));
                bwx_fact.AddFact(new Fact<Entity>(speed, s));
                bwx_fact.AddFact(new Fact<Entity>(loop, TestModule.ent_true));
                space.Post(new Note(bwx_fact, bwx_task));
                bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_wait));
                bwx_fact.AddFact(new Fact<Entity>(time, t));
                space.Post(new Note(bwx_fact, bwx_task));
            }while(false);
            bwx_task = bwx_task_0;
            yield return TaskStatus.Success;
        }
        public static void RandomMoveStub(Expert expert, Space space, Fact arg)
        {
            Method method = new Method(note.Author);
            method.Enumerable = ((Doggie)expert).RandomMove(method, space, note);
            method.Schedule();
        }
        public IEnumerable<TaskStatus> RandomTurn(Method method, Space space, Note note)
        {
            Task bwx_task, bwx_task_0, bwx_task_1, bwx_task_2;
            Fact bwx_fact;
            bwx_task = method;
            do{
                bwx_task_0 = bwx_task;
                bwx_task = new ProbabilitySelect(bwx_task);
                if(bwx_weight < 0.5)
                {
                    do{
                        bwx_task_1 = bwx_task;
                        bwx_task = new Case(bwx_task);
                        do{
                            bwx_task_2 = bwx_task;
                            bwx_task = new Parallel(bwx_task);
                            bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_rotate));
                            bwx_fact.AddFact(new Fact<Entity>(degree, 1.0));
                            space.Post(new Note(bwx_fact, bwx_task));
                            bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_animate));
                            bwx_fact.AddFact(new Fact<Entity>(name, "TurnLeft"));
                            bwx_fact.AddFact(new Fact<Entity>(speed, 1.0));
                            bwx_fact.AddFact(new Fact<Entity>(loop, TestModule.ent_true));
                            space.Post(new Note(bwx_fact, bwx_task));
                            bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_wait));
                            bwx_fact.AddFact(new Fact<Entity>(time, t));
                            bwx_fact.AddFact(new Fact<Entity>(random, t));
                            space.Post(new Note(bwx_fact, bwx_task));
                        }while(false);
                        bwx_task = bwx_task_2;
                    }while(false);
                    bwx_task = bwx_task_1;
                }
                else if(bwx_weight < 1)
                {
                    do{
                        bwx_task_1 = bwx_task;
                        bwx_task = new Case(bwx_task);
                        do{
                            bwx_task_2 = bwx_task;
                            bwx_task = new Parallel(bwx_task);
                            bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_rotate));
                            bwx_fact.AddFact(new Fact<Entity>(degree, -1.0));
                            space.Post(new Note(bwx_fact, bwx_task));
                            bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_animate));
                            bwx_fact.AddFact(new Fact<Entity>(name, "TurnRight"));
                            bwx_fact.AddFact(new Fact<Entity>(speed, 1.0));
                            bwx_fact.AddFact(new Fact<Entity>(loop, TestModule.ent_true));
                            space.Post(new Note(bwx_fact, bwx_task));
                            bwx_fact = new Fact<Entity>(TestModule.ent_I, TestModule.ent_perform, TestModule.ent_wait));
                            bwx_fact.AddFact(new Fact<Entity>(time, t));
                            bwx_fact.AddFact(new Fact<Entity>(random, t));
                            space.Post(new Note(bwx_fact, bwx_task));
                        }while(false);
                        bwx_task = bwx_task_2;
                    }while(false);
                    bwx_task = bwx_task_1;
                }
            }while(false);
            bwx_task = bwx_task_0;
            yield return TaskStatus.Success;
        }
        public static void RandomTurnStub(Expert expert, Space space, Fact arg)
        {
            Method method = new Method(note.Author);
            method.Enumerable = ((Doggie)expert).RandomTurn(method, space, note);
            method.Schedule();
        }
    }
    public class TestModule : Module
    {
        public IEnumerable<TaskStatus> Main(Method method, Space space, Note note)
        {
            Task bwx_task, bwx_task_0, bwx_task_1, bwx_task_2;
            Fact bwx_fact;
            bwx_task = method;
            yield return TaskStatus.Success;
        }
        public static void MainStub(Expert expert, Space space, Fact arg)
        {
            Method method = new Method(note.Author);
            method.Enumerable = ((TestModule)expert).Main(method, space, note);
            method.Schedule();
        }
        static Entity ent_name = EntityManager.Instance().Intern("name");
        static Entity ent_speed = EntityManager.Instance().Intern("speed");
        static Entity ent_time = EntityManager.Instance().Intern("time");
        static Entity ent_degree = EntityManager.Instance().Intern("degree");
        static Entity ent_loop = EntityManager.Instance().Intern("loop");
        static Entity ent_I = EntityManager.Instance().Intern("I");
        static Entity ent_perform = EntityManager.Instance().Intern("perform");
        static Entity ent_bodily = EntityManager.Instance().Intern("bodily");
        static Entity ent_active = EntityManager.Instance().Intern("active");
        static Entity ent_passive = EntityManager.Instance().Intern("passive");
        static Entity ent_animate = EntityManager.Instance().Intern("animate");
        static Entity ent_false = EntityManager.Instance().Intern("false");
        static Entity ent_random_turn = EntityManager.Instance().Intern("random_turn");
        static Entity ent_random_move = EntityManager.Instance().Intern("random_move");
        static Entity ent_true = EntityManager.Instance().Intern("true");
        static Entity ent_translate = EntityManager.Instance().Intern("translate");
        static Entity ent_wait = EntityManager.Instance().Intern("wait");
        static Entity ent_rotate = EntityManager.Instance().Intern("rotate");
    }
}
