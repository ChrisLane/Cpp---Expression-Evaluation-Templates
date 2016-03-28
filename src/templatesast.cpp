template<typename V>
V Constant<V>::eval(env<V> *) {
    return c;
}

template<typename V>
V Var<V>::eval(env<V> *environment) {
    while (environment) {
        if (name.compare(environment->var) == 0) {
            return environment->value;
        } else {
            environment = environment->next;
        }
    }
    return 0;
}

template<typename V>
V OpApp<V>::eval(env<V> *environment) {
    V acc = ops.unit;
    ExpList<V> *list = args;
    while (list) {
        acc = ops.binop(acc, list->head->eval(environment));
        list = list->tail;
    }
    return acc;
}

template<typename V>
V Let<V>::eval(env<V> *environment) {
    env<V> *newEnvironment = new env<V>;
    newEnvironment->var = bvar;
    newEnvironment->value = bexp->eval(environment);
    newEnvironment->next = environment;

    return body->eval(newEnvironment);
}