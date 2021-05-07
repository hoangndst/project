import React, { useLayoutEffect } from 'react'
import { StyleSheet, Text, View, SafeAreaView, Button } from 'react-native'
import { StatusBar } from 'expo-status-bar'
import { Avatar } from 'react-native-elements'
import { ScrollView } from 'react-native-gesture-handler'
import CustomListItem from '../components/CustomListItem'
import { auth, db } from '../firebase'


const HomeScreen = ({ navigation }) => {
    useLayoutEffect(() => {
        navigation.setOptions({
            title: "Your Fucking Signal",
            headerLeft: () => {
                <View style={{ marginLeft: 10 }}>
                    <Avatar
                        rounded
                        source={{
                            uri: auth?.currentUser?.photoURL
                        }}
                    />
                </View>
               
            },
        });
    }, []);
    return (
        <SafeAreaView>
            <StatusBar style='light'/>
            <ScrollView>
                <CustomListItem/>
                <View style={{ marginLeft: 10 }}>
                    <Avatar
                        rounded
                        source={{
                            uri: auth?.currentUser?.photoURL
                        }}
                    />
                </View>
            </ScrollView>
        </SafeAreaView>
    )
}

export default HomeScreen

const styles = StyleSheet.create({})
