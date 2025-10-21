package com.example.m2_jetpack

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.material3.*
import androidx.compose.runtime.Composable
import androidx.navigation.compose.*
import com.example.m2_jetpack.ui.TelaA
import com.example.m2_jetpack.ui.TelaB

class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            MaterialTheme {
                AppNavigation()
            }
        }
    }
}

@Composable
fun AppNavigation() {
    val navController = rememberNavController()

    NavHost(
        navController = navController,
        startDestination = "telaA"
    ) {
        composable("telaA") {
            TelaA(navController)
        }
        composable("telaB/{nome}") { backStackEntry ->
            val nome = backStackEntry.arguments?.getString("nome")
            TelaB(nome)
        }
    }
}
