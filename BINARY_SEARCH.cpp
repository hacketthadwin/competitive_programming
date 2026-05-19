int l=lowest_possible_value-1,r=highest_possible_value,m;
while(r-l>1)
{
    m=l+(r-l)/2;if(f(m))r=m;else l=m;
}
return r;
// and vice versa if you want to find the highest x satisfying g(x):

int l=lowest_possible_value,r=highest_possible_value+1,m;
while(r-l>1)
{
    m=l+(r-l)/2;if(g(m))l=m;else r=m;
}
return l;


// for minimize the maximum type questions -> use first one
// for maximise the minimum type questions -> use second one

// second one gives maximum value, first one gives minimum value

// always correct until you take out edge cases in predicate function

// also it gives weird error (different than other runtime errors) if you forget to do m=l+(r-l)/2;

// also i learnt very important thing today

// in this my template there is a catch,

// first let's see my template

// 1. if you want to find the lowest x satisfying f(x):

int l=lowest_possible_value-1,r=highest_possible_value,m;
while(r-l>1)
{
    m=l+(r-l)/2;if(f(m))r=m;else l=m;
}
return r;

// THE ABOVE PATTERN ASSUMES FFFFFTTTTT and it assumes that there is definately one T and one F, so if no true case is also possible, that is FFFFFF 
// then i should make r=highest_possible_value+1 
// and if true is guaranteed possible then r=highest_possible_value


// 2. and vice versa if you want to find the highest x satisfying g(x):

int l=lowest_possible_value,r=highest_possible_value+1,m;
while(r-l>1)
{
    m=l+(r-l)/2;if(g(m))l=m;else r=m;
}
return l;

// THE SECOND PATTERN ASSUMES TTTTTFFFFF and it assumes that there is definately one T and one F, so if no true case is also possible, that is FFFFFF 
// then i should make r=lowest_possible_value-1
// and if true is guaranteed possible then r=lowest_possible_value

// Similarly:
// If false may not exist in this template:
// TTTTTT
// then you need virtual false boundary:
// r = highest_possible_value + 1



// so summarising, 
// 1. First TRUE (lowest x satisfying)

// Pattern:

// FFFFTTTT

// Template:

// while(r-l>1)
// {
//     m=l+(r-l)/2;
//     if(f(m)) r=m;
//     else l=m;
// }
// return r;

// Invariant:

// f(l)=false
// f(r)=true

// Initialization:

// If TRUE guaranteed:
// l = lowest_possible_value - 1
// r = highest_possible_true_value
// If TRUE may not exist:
// l = lowest_possible_value - 1
// r = highest_possible_value + 1   // virtual true
// 2. Last TRUE (highest x satisfying)

// Pattern:

// TTTTFFFF

// Template:

// while(r-l>1)
// {
//     m=l+(r-l)/2;
//     if(g(m)) l=m;
//     else r=m;
// }
// return l;

// Invariant:

// g(l)=true
// g(r)=false

// Initialization:

// If TRUE guaranteed:
// l = lowest_possible_true_value
// r = highest_possible_value + 1
// If TRUE may not exist:
// l = lowest_possible_value - 1   // virtual true
// r = highest_possible_value + 1


// ****If one side may not exist, create virtual boundary****
